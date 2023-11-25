
# Tester Grafos Algoritmos Básico

## Descripción 📚

Este repositorio contiene un programa en C++ diseñado para representar grafos y ejecutar algoritmos de shortest path. El programa ofrece una interfaz básica de texto y es expandible para la implementación de nuevos algoritmos.

## Instrucciones de Ejecución ⚙️

Para ejecutar el programa, utiliza el acceso directo en la carpeta `Tester Grafos Algoritmos Basico`:

- `Tester Grafos Algoritmos Basico.exe`

También puedes ejecutar el programa directamente desde la carpeta `build`:

- `./build/main.exe`

Si deseas ejecutar el programa sin el código fuente en C++, puedes eliminar la carpeta `src/`.

## Estructura de Archivos 📁

- `build/`: Contiene el ejecutable principal.
- `data/import/`: Almacena archivos para importar.
- `data/export/`: Guarda archivos exportados.
- `src/`: Contiene el código fuente.
  - `controller/`: Controladores del programa.
  - `model/`: Modelos, incluida la clase `ShortestPath.h` donde se pueden agregar nuevos algoritmos.
  - `view/`: Vistas, incluido el archivo `runShortestPath.h` que funciona como un menú para ejecutar los algoritmos.

## Edición del Código ✍️

Si deseas readaptar el código para añadir nuevos algoritmos, las clases principales son:

- `model/ShortestPath.h`: Agrega nuevos algoritmos de shortest path aquí.
- `view/runShortestPath.h`: Implementa la ejecución de los algoritmos definidos en `ShortestPath.h`.

## Nota Importante 🚨

Mantén la estructura de archivos mencionada para garantizar la correcta exportación e importación de datos.

## Configuración Recomendada para Visual Studio Code ⚙️

Se recomienda el uso de Visual Studio Code para el desarrollo y compilación del programa. A continuación, se detallan los pasos para configurar el entorno de desarrollo:

1. **Instalación de Mingw con MSYS2:**
   Asegúrate de tener Mingw instalado con MSYS2 para compilar el código C++ de manera efectiva.
2. **Instalación de Visual Studio Code:**
   Descarga e instala Visual Studio Code desde [https://code.visualstudio.com/](https://code.visualstudio.com/).
3. **Instalación de la Extensión C/C++ Compile Run:**
   En Visual Studio Code, instala la extensión C/C++ Compile Run de danielpinto8zz6. Puedes encontrar la extensión [aquí](https://github.com/danielpinto8zz6/c-cpp-compile-run).
4. **Configuración de la Extensión:**

   - Abre el archivo `main.cpp` en Visual Studio Code.
   - Ve a la configuración de la extensión C/C++ Compile Run.
   - En "Output-location", configura la ubicación del archivo de salida a "../../build" para asegurar que los archivos compilados se almacenen en la carpeta adecuada.

Con esta configuración, podrás compilar y ejecutar el programa de manera sencilla directamente desde Visual Studio Code.
