-- Crear la tabla automovil--
CREATE TABLE automovil (
    id_automovil NUMBER PRIMARY KEY,
    marca VARCHAR2(50),
    modelo VARCHAR2(50),
    anio_fabricacion NUMBER,
    color VARCHAR2(20),
    precio NUMBER
);

-- Insertar ejemplos de instancias en la tabla--
INSERT INTO automovil (id_automovil, marca, modelo, anio_fabricacion, color, precio)
VALUES (1, 'Toyota', 'Corolla', 2022, 'Azul', 25000);

INSERT INTO automovil (id_automovil, marca, modelo, anio_fabricacion, color, precio)
VALUES (2, 'Honda', 'Civic', 2021, 'Rojo', 23000);

INSERT INTO automovil (id_automovil, marca, modelo, anio_fabricacion, color, precio)
VALUES (3, 'Ford', 'Focus', 2023, 'Negro', 22000);
