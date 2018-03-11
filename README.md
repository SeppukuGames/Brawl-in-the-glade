### TRABAJAR CON EL PROYECTO

* Git clone de este repositorio
* Bajarse de Drive: Ogre.zip
* Crear carpeta Proyecto3: Dependencies
* Extraer Ogre.zip en Dependencies


### PASOS PARA MONTAR EL BUILD EN EL PROYECTO

* Abrimos el programa CMake-GUI (El CMake se encuentra en el Repositorio CMake)

	1. En el apartado: **Where is the source code**: Meter la ruta del directorio Src de Ogre **Proyecto3->Ogre**

	2. En el apartado **Where to build the binaries**: Meter la ruta del directorio que hemos creado: Ogre **Proyecto3->Ogre->build**
		La carpeta build la tenemos que crear a mano porque se ignora en el .gitignore.

	3. Clickar en Configure, donde tendremos que elegir el generador ---> **Visual Studio 12 2013**

	4. Desactivamos aquello que no usaremos:

		* PYTHON
		* JAVA
		* LOS DOS APARTADOS DE SAMPLES
		* TODOS LOS RENDERSYSTEM EXCEPTO GL3PLUS
		* DIRECTX

		Aunque no lo podamos usar, vamos a dejar Ogre_Bites.

	5. Click en **Generar**, dos veces.

* Una vez creada la carpeta **build**, abrimos la solucion OGRE.sln que se encuentra en la carpeta **build**   Proyecto3->Ogre->build->OGRE.sln

* Compilamos el proyecto **ALL_BUILD** en **Release** y en **Debug** 

En principio, debería funcionar.






