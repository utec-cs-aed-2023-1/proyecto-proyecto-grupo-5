<h1 align="center">Estructuras de datos</h1>

## DoubleList (Lista doblemente enlazada)

El uso de una lista doblemente enlazada (DoubleList) puede ser útil en varias partes de la implementación.

Escenarios donde se puede utilizar **doublelist**:

1. *Mantenimiento del historial de transacciones*: Utilizar una lista doblemente enlazada para mantener un historial ordenado cronológicamente de las transacciones registradas en la aplicación. Cada nodo de la lista contendría los detalles de una transacción, y los enlaces entre los nodos permitirían un recorrido eficiente tanto hacia adelante como hacia atrás en el historial. Esto sería útil para mostrar el historial de transacciones a los usuarios, realizar búsquedas en el historial o para fines de auditoría.


2. *Almacenamiento ordenado de transacciones*: Puedes utilizar la lista doblemente enlazada para almacenar y mantener un registro ordenado de las transacciones de retiro de dinero. Cada nodo de la lista podría representar una transacción y contener la información relevante, como el cliente, el lugar, el monto y la fecha. La lista te permitirá agregar nuevas transacciones de manera eficiente, mantenerlas ordenadas según la fecha y acceder a ellas fácilmente para consultas o análisis.

3. *Operaciones de inserción y eliminación eficientes*: La lista doblemente enlazada es eficiente para realizar operaciones de inserción y eliminación en cualquier posición de la lista. Por ejemplo, si necesitas insertar una nueva transacción en una posición específica según la fecha, puedes aprovechar los punteros previos y siguientes de los nodos para realizar la inserción de manera eficiente. Del mismo modo, si deseas eliminar una transacción de la lista, los punteros te permitirán actualizar las referencias correctamente sin afectar el resto de la lista.

4. *Recorrido bidireccional de la lista*: Al ser una lista doblemente enlazada, puedes recorrerla tanto hacia adelante como hacia atrás. Esto puede ser útil si necesitas realizar operaciones de búsqueda o análisis en las transacciones en función de diferentes criterios, como buscar transacciones de un cliente específico o realizar un análisis histórico de los retiros.  

## Hash
1. *Almacenamiento eficiente de transacciones*: Puedes utilizar una tabla hash para almacenar las transacciones de retiro de dinero. Cada transacción puede tener un identificador único, como el número de transacción, y la tabla hash puede usar ese identificador como clave para acceder rápidamente a la transacción correspondiente. Esto te permitirá almacenar y recuperar las transacciones de forma eficiente sin tener que recorrer una lista o una estructura más compleja.

2. *Búsqueda rápida de transacciones*: Si necesitas buscar transacciones de retiro de dinero según criterios específicos, como el número de cliente o la fecha, una tabla hash puede ser muy útil. Puedes utilizar diferentes campos de la transacción como claves en la tabla hash y realizar búsquedas rápidas basadas en esos campos. Por ejemplo, si quieres encontrar todas las transacciones de un cliente en particular, simplemente buscarías en la tabla hash utilizando el identificador del cliente como clave.

3. *Detección de transacciones duplicadas*: La tabla hash puede ayudarte a evitar la inserción de transacciones duplicadas de retiro de dinero. Puedes utilizar la función de hash para generar una clave única para cada transacción y verificar si ya existe una transacción con la misma clave en la tabla hash. Esto te permitirá evitar la duplicación de transacciones y mantener la integridad de los datos.

## Heap

1. *Priorización de transacciones*: Si deseas procesar las transacciones de retiro de dinero en un orden específico, puedes utilizar un heap para mantener un orden de prioridad. Por ejemplo, si tienes transacciones urgentes que requieren un procesamiento rápido, puedes asignarles una mayor prioridad y colocarlas en la parte superior del heap. De esta manera, puedes garantizar que las transacciones más importantes se procesen primero.

2. *Gestión de límites de retiro*: Si tienes límites de retiro establecidos para cada cliente, un heap puede ayudarte a garantizar que se cumplan esos límites. Puedes mantener un heap de transacciones pendientes, ordenadas por la cantidad de dinero a retirar. Al procesar cada transacción, verificas si el retiro excede el límite establecido para ese cliente. Si es así, puedes rechazar la transacción o tomar alguna otra acción según tus requisitos.

