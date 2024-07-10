CREATE TABLE `alumnos` (
  `idAlumno` int NOT NULL AUTO_INCREMENT,
  `apellido` varchar(30) NOT NULL,
  `nombre` varchar(30) NOT NULL,
  `fechaNacimiento` date NOT NULL,
  `dni` int NOT NULL,
  PRIMARY KEY (`idAlumno`)
);

CREATE TABLE `cursos` (
  `idCurso` int NOT NULL AUTO_INCREMENT,
  `curso` int NOT NULL,
  `division` varchar(1) NOT NULL,
  `descripcion` varchar(15) NOT NULL,
   `nivel` varchar(1) NOT NULL,
  PRIMARY KEY (`idCurso`)
) ;

CREATE TABLE `cursoAlumno` (
  `idCursoAlumno` int NOT NULL AUTO_INCREMENT,
  `idCurso` int NOT NULL,
  `idAlumno` int NOT NULL,
  `anio_lectivo` int NOT NULL,
  PRIMARY KEY (`idCursoAlumno`),
    FOREIGN KEY (idCurso) REFERENCES cursos(idCurso),
    FOREIGN KEY (idAlumno) REFERENCES alumnos(idAlumno)
) ;

CREATE TABLE `materias` (
  `idMateria` int NOT NULL AUTO_INCREMENT,
  `nombreMateria` varchar(20) NOT NULL,

  `nivel` varchar(1) NOT NULL,
  PRIMARY KEY (`idMateria`)
);

CREATE TABLE `cursoMateria` (
  `idMateriaCurso` int NOT NULL AUTO_INCREMENT,
  `idCurso` int NOT NULL,
  `idMateria` int NOT NULL,
  `anio_lectivo` int NOT NULL,
  PRIMARY KEY (`idMateriaCurso`),
    FOREIGN KEY (idCurso) REFERENCES cursos(idCurso),
    FOREIGN KEY (idMateria) REFERENCES materias(idMateria)
);
