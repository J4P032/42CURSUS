Documentación https://www.prisma.io/

Primeros pasos para inst alar prisma
	Tener NodeJS
	Tener npm

Pasos
	npm i prisma -D		// -D indica Desarrollo
		se instalan los modulos que podremos usar
	npx prisma init --datasource-provider postgresql
		se crea:
			el schema para crear las tablas
			el .env donde indicar la conexión a la base de datos (direccion y puerto)
				la direccion debería ser asi:
					postgresql://user:password@localhost:5432/transcendence"
	npx prisma migrate dev
		tras la configuracion hay que crear las tablas y para ello hay que hacer migraciones
			las migraciones son las conversiones a SQL
			al jecutar el camando te pedirá nombre para la migracion
			las migraciones se guardan en la carpeta migrations dento de prisma como si fuera un historial
			
		
			