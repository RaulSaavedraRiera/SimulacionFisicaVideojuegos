# SimulacionFisicaVideojuegos
Repositorio de las prácticas de la asignatura de Simulación Física de Videojuegos

En la carpeta skeleton estará vuestro código fuente

Necesitaréis además descomprimir el archivo que se indica a continuación en la raíz del repositorio:

Carpetas bin y common https://ucomplutense-my.sharepoint.com/:u:/g/personal/davalejo_ucm_es/EZcsdyIoqTFOrF4hdfkVYk0BJZ9IycJ3QqXQFwaXVrlSKg?e=pfs6IO



Resumen :

El proyecto realizado es un runner procedural. Donde el jugador deberá llegar al final del mapa superando las diferentes pruebas generadas de forma aleatoria sin ser golpeado o salirse de la pista; en cuyo caso deberá de volver a comenzar desde el principio.
El jugador es una pelota y puede desplazarse en las cuatro direcciones rotando sobre sí mismo. Además de los diferentes obstáculos diferentes pueden afectar sobre él diferentes fuerzas que tendrá que tener en cuenta a la hora de avanzar.
Los objetos sólidos desplazarán la player pudiendo hacerle caer, las partículas; si golpean al player, harán que este vuelva a empezar desde cero; al igual que si cae al vacío.

Controles:

Básicos

-WASD para desplazarse.

-Si se cae al vacío se resetea a la posición inicial.

-Si el jugador es golpeado por algunas partículas se resetea a la posición inicial.

Para testear

-Se puede cambiar el número de fases en el WorldManager en el GenerateLevel modificando el número de plataformas, así como la inicial y el final (GenerateFloor); se ruega no modificar value o currentValue para no crear sobreexposición de elementos. Si se quieren ir probando diferentes secciones por separado se puede realizar de la siguiente manera:
generateFloor({ 0,0, 0 });
generateXType({0,0,value)};


-Si se quiere reducir la distancia de victoria se puede modificar cambiando la variable winZ en el método GenerateLevel del WorldManager

PAra mas información pdf adjunto