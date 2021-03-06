#ifndef MOUSECOMPONENT_H_
#define MOUSECOMPONENT_H_

#include "Component.h"
#include "MouseInputComponent.h"
#include "Factory.h"
#include "GameObject.h"
#include <iostream>
#include "OgreMesh.h"
#include <OgreSubMesh.h>
#include "OgreMovableObject.h"
#include "OgreEntity.h"
#include "OgreNode.h"
#include "DynamicRigidbodyComponent.h"

using namespace Ogre;


class MouseComponent : public MouseInputComponent
{

public:

	MouseComponent(Ogre::Camera * cam) : MouseInputComponent()
	{
		Cam = cam;
	}

	virtual ~MouseComponent()
	{
	}

	virtual void start(){
		raySceneQuery = _gameObject->getNode()->getCreator()->createRayQuery(Ray());
		idBala = -1;
		currentCD = 0;
		resultado = Vector3(0, 0, 0);
		btVector3 aux (0.0f, 1.0f, 0.0f);
		newRotation = btQuaternion(aux, 0.0f);
		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));

	};

	virtual void tick(double elapsed){
		currentCD +=  1 + elapsed;	//Sumo el cooldown hasta que llegue a Cooldown, entonces podr� disparar
	};

	void GetMeshInformation(const Ogre::MeshPtr mesh,
		size_t &vertex_count,
		Ogre::Vector3* &vertices,
		size_t &index_count,
		unsigned long* &indices,
		const Ogre::Vector3 &position,
		const Ogre::Quaternion &orient,
		const Ogre::Vector3 &scale)
	{
		bool added_shared = false;
		size_t current_offset = 0;
		size_t shared_offset = 0;
		size_t next_offset = 0;
		size_t index_offset = 0;

		vertex_count = index_count = 0;

		// Calculate how many vertices and indices we're going to need
		for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
		{
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);

			// We only need to add the shared vertices once
			if (submesh->useSharedVertices)
			{
				if (!added_shared)
				{
					vertex_count += mesh->sharedVertexData->vertexCount;
					added_shared = true;
				}
			}
			else
			{
				vertex_count += submesh->vertexData->vertexCount;
			}

			// Add the indices
			index_count += submesh->indexData->indexCount;
		}


		// Allocate space for the vertices and indices
		vertices = new Ogre::Vector3[vertex_count];
		indices = new unsigned long[index_count];

		added_shared = false;

		// Run through the submeshes again, adding the data into the arrays
		for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
		{
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);

			Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

			if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
			{
				if (submesh->useSharedVertices)
				{
					added_shared = true;
					shared_offset = current_offset;
				}

				const Ogre::VertexElement* posElem =
					vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

				Ogre::HardwareVertexBufferSharedPtr vbuf =
					vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

				unsigned char* vertex =
					static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

				// There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
				//  as second argument. So make it float, to avoid trouble when Ogre::Real will
				//  be comiled/typedefed as double:
				//      Ogre::Real* pReal;
				float* pReal;

				for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
				{
					posElem->baseVertexPointerToElement(vertex, &pReal);

					Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

					vertices[current_offset + j] = (orient * (pt * scale)) + position;
				}

				vbuf->unlock();
				next_offset += vertex_data->vertexCount;
			}


			Ogre::IndexData* index_data = submesh->indexData;
			size_t numTris = index_data->indexCount / 3;
			Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
			if (ibuf.isNull()) continue; // need to check if index buffer is valid (which will be not if the mesh doesn't have triangles like a pointcloud)

			bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

			unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);


			size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;
			size_t index_start = index_data->indexStart;
			size_t last_index = numTris * 3 + index_start;

			if (use32bitindexes)
				for (size_t k = index_start; k < last_index; ++k)
				{
					indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
				}

			else
				for (size_t k = index_start; k < last_index; ++k)
				{
					indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
						static_cast<unsigned long>(offset);
				}

			ibuf->unlock();
			current_offset = next_offset;
		}
	}

	bool RaycastFromPoint(Ogre::Real posMouseX, Ogre::Real posMouseY,
		Vector3 &result)
	{
		// create the ray to test
		Ogre::Ray ray = Cam->getCameraToViewportRay(posMouseX, posMouseY);

		// check we are initialised
		if (raySceneQuery != NULL)
		{
			// create a query object
			raySceneQuery->setRay(ray);

			// execute the query, returns a vector of hits
			if (raySceneQuery->execute().size() <= 0)
			{
				// raycast did not hit an objects bounding box
				return (false);
			}
		}
		else
		{
			return (false);
		}

		// at this point we have raycast to a series of different objects bounding boxes.
		// we need to test these different objects to see which is the first polygon hit.
		// there are some minor optimizations (distance based) that mean we wont have to
		// check all of the objects most of the time, but the worst case scenario is that
		// we need to test every triangle of every object.
		Ogre::Real closest_distance = -1.0f;
		Ogre::Vector3 closest_result;
		Ogre::RaySceneQueryResult &query_result = raySceneQuery->getLastResults();
		for (size_t qr_idx = 0; qr_idx < query_result.size(); qr_idx++)
		{
			// stop checking if we have found a raycast hit that is closer
			// than all remaining entities
			if ((closest_distance >= 0.0f) &&
				(closest_distance < query_result[qr_idx].distance))
			{
				break;
			}

			// only check this result if its a hit against an entity
			if ((query_result[qr_idx].movable != NULL) &&
				(query_result[qr_idx].movable->getMovableType().compare("Entity") == 0))
			{
				// get the entity to check
				Ogre::Entity *pentity = static_cast<Ogre::Entity*>(query_result[qr_idx].movable);

				// mesh data to retrieve         
				size_t vertex_count;
				size_t index_count;
				Ogre::Vector3 *vertices;
				unsigned long *indices;

				// get the mesh information
				GetMeshInformation(pentity->getMesh(), vertex_count, vertices, index_count, indices,
					pentity->getParentNode()->getPosition(),
					pentity->getParentNode()->getOrientation(),
					pentity->getParentNode()->_getDerivedScale());

				// test for hitting individual triangles on the mesh
				bool new_closest_found = false;
				for (int i = 0; i < static_cast<int>(index_count); i += 3)
				{
					// check for a hit against this triangle
					std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]],
						vertices[indices[i + 1]], vertices[indices[i + 2]], true, false);

					// if it was a hit check if its the closest
					if (hit.first)
					{
						if ((closest_distance < 0.0f) ||
							(hit.second < closest_distance))
						{
							// this is the closest so far, save it off
							closest_distance = hit.second;
							new_closest_found = true;
						}
					}
				}

				// free the verticies and indicies memory
				delete[] vertices;
				delete[] indices;

				// if we found a new closest raycast for this object, update the
				// closest_result before moving on to the next object.
				if (new_closest_found)
				{
					closest_result = ray.getPoint(closest_distance);
				}
			}
		}

		// return the result
		if (closest_distance >= 0.0f)
		{
			// raycast success
			result = closest_result;
			return (true);
		}
		else
		{
			// raycast failed
			return (false);
		}
	}

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
		//Click izquierdo: Dispara la bala.
		Viewport * vp = _gameObject->getNode()->getCreator()->getCurrentViewport();
		posMouseX = arg.state.X.abs / Real(vp->getActualWidth());;
		posMouseY = arg.state.Y.abs / Real(vp->getActualHeight());;
		std::cout << "x: " << posMouseX << " y: " << posMouseY << std::endl;

		if (id == OIS::MB_Left && currentCD >= Cooldown){
			//Dispara una bala.
			
			RaycastFromPoint(posMouseX, posMouseY, resultado);
	
			
			btVector3 newLook(resultado.x, 0, resultado.z);
			btVector3 posJugador = transform.getOrigin();
			btScalar laX = newLook.getX() - posJugador.getX();
			btScalar laZ = newLook.getZ() - posJugador.getZ();

			btVector3 vectDir(laX, 0.0f, laZ);

			idBala++;	//Empieza en 0
			std::string nombreBala = std::to_string(idBala);
			BulletFactory::creaBala(_gameObject->getNode()->getCreator(), transform.getOrigin(), vectDir, nombreBala);

			//Reiniciamos cooldown
			currentCD = 0;
			
		}

		return true;
	}


	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
		return true;
	};


	//Cada vez que movemos el rat�n vamos guardando sus coodenadas
	virtual bool mouseMoved(const OIS::MouseEvent &arg)
	{
		Plane mPlane(Vector3::UNIT_Y, 0);

		// get window height and width
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

		// convert to 0-1 offset
		Ogre::Real offsetX = arg.state.X.abs / screenWidth;
		Ogre::Real offsetY = arg.state.Y.abs / screenHeight;

		// set up the ray
		Ray mouseRay = Cam->getCameraToViewportRay(offsetX, offsetY);

		// check if the ray intersects our plane
		// intersects() will return whether it intersects or not (the bool value) and
		// what distance (the Real value) along the ray the intersection is
		std::pair<bool, Real> result = mouseRay.intersects(mPlane);

		if (result.first) {
			// if the ray intersect the plane, we have a distance value
			// telling us how far from the ray origin the intersection occurred.
			// the last thing we need is the point of the intersection.
			// Ray provides us getPoint() function which returns a point
			// along the ray, supplying it with a distance value.

			// get the point where the intersection is
			resultado = mouseRay.getPoint(result.second);
			transform = rb->getRigidbody()->getWorldTransform();

			// assume that "forward" for the player in local-frame is +zAxis
			// and that the player is constrained to rotate about yAxis (+yAxis is "up")
			btVector3 localLook(0.0f, 0.0f, 1.0f); // zAxis
			btVector3 rotationAxis(0.0f, 1.0f, 0.0f); // yAxis

			//btTransform identity = transform.getIdentity();
			btQuaternion rotation = transform.getRotation();
			btVector3 rotVector(rotation.getX(), rotation.getY(), rotation.getZ());
			// compute currentLook and angle
			btVector3 currentLook = localLook * -rotation.getW();
			btVector3 newLook(resultado.x, 0, resultado.z);
			btScalar angle;

			if (resultado.x >= 0) {
				angle = currentLook.angle(newLook);
				angle = -angle;
			}
			else {
				angle = currentLook.angle(newLook);
			}

			//std::cout << "Angulo rotacion: " << newLook.getX() << std::endl;
			// compute new rotation
			btQuaternion deltaRotation(rotationAxis, angle);
			newRotation = deltaRotation * rotation;

			// apply new rotation
			transform.setRotation(newRotation);
			rb->getRigidbody()->setCenterOfMassTransform(transform);
			rb->getRigidbody()->getMotionState()->setWorldTransform(transform);
			rb->getRigidbody()->getMotionState()->setWorldTransform(btTransform(newRotation, transform.getOrigin()));

		}


		return true;
	}

	Vector3 getMousePos(){
		return resultado;
	}

	btQuaternion getRotation(){
		return newRotation;
	}

	btTransform getTransform(){
		return transform;
	}
private:

	const double Cooldown = 7;
	double currentCD;

	RaySceneQuery *raySceneQuery;

	Ogre::Real posMouseX, posMouseY;
	btQuaternion dirBala;
	int idBala;
	btQuaternion newRotation;


	Vector3 resultado;
	Ogre::Camera * Cam;
	Ogre::AxisAlignedBox plano;

	DynamicRigidbodyComponent *rb;
	btTransform transform;
};

#endif /* MOVECAMERACOMPONENT_H_ */

