### TRABAJAR CON EL PROYECTO

* Git clone de este repositorio
* Ya puedes trabajar

### CARGAR RECURSOS PARA EL PROYECTO
	Debido a un error, para utilizar recursos de Ogre vamos a tener que adjuntarlos independientemente según los necesitemos.

	*Los archivos de Ogre están en **Dependencies -> Ogre**, pero sólo vamos a querer los archivos necesarios.

	--¿Cómo sé qué archivos necesito?--

	1. Buscar el mesh que quieras en la carpeta Ogre, en el **buscador de archivos**

	2. Añadir el mesh al proyecto. 

	3. Debería salir el modelo en gris. Ahora hay que **Consultar el logs** para ver qué más falta.
		- El logs se encuentra en la ruta **Exes -> OgreD -> Ogre.log**
		- Aquí te va a especificar las texturas, materiales y demás que necesite la malla.

	4. Buscar de forma individual **cada uno** de los archivos necesarios, también con el **buscador de archivos**, y ponerlo en las carpetas correspondientes en **Media -> Materials/Mesh/Textures**