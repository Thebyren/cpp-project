BEGIN TRANSACTION;

INSERT INTO Empleados (tipo_empleado) VALUES (1);
UPDATE Empleados SET id_compuesto = 'FNU' || id_empleado || 'A' WHERE tipo_empleado = 1;

COMMIT;