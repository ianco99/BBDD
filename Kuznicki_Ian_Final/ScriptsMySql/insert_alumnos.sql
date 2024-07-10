 INSERT INTO `tp_enzocoletta`.`alumnos` ( `apellido`,`nombre`,`fechaNacimiento`,`dni`) VALUES( 'Garcia','Carmelo','1994/04/22', 33009897);
 
 
 
ALTER TABLE alumnos ADD UNIQUE uk_dnialumno (dni);


 INSERT INTO `tp_enzocoletta`.`alumnos` ( `apellido`,`nombre`,`fechaNacimiento`,`dni`) VALUES( 'Garcia Fernandez','Carmelo','1994/04/22', 33009897);  
 
 insert into cursoalumno (idcurso, idalumno, anio_lectivo) values (1,2,2023);
 
 insert into  cursoalumno (idcurso, idalumno, anio_lectivo) values (1,1,2023);
 insert into  cursoalumno (idcurso, idalumno, anio_lectivo) values (5,3,2023);