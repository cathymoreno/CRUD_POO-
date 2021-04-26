#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "ConexionBD.h"
#include "Persona.h"


using namespace std;

class Cliente : Persona {
private: string nit;
	   // constructor
public:
	Cliente() {
	}
	Cliente(string nom, string ape, string dir, int tel, string fn, string n) : Persona(nom, ape, dir, tel, fn) {
		nit = n;
	}

	// METODOS
	//set (modificar)
	void setNit(string n) { nit = n; }
	void setNombres(string nom) { nombres = nom; }
	void setApellidos(string ape) { apellidos = ape; }
	void setDireccion(string dir) { direccion = dir; }
	void setTelefono(int tel) { telefono = tel; }
	void setFecha_Nacimiento(int fn) { fecha_nacimiento = fn; }
	//get (mostrar)
	string getNit() { return nit; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getDireccion() { return direccion; }
	int getTelefono() { return telefono; }
	string getFecha_Nacimiento() { return fecha_nacimiento; }

	//ELIMINAR
	void eliminar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		system("cls");
		int id_eliminar;
		string insert;
		cout << "Ingrese Id a eliminar: ";
		cin >> id_eliminar;
		insert = "delete from clientes where id_cliente = " + to_string(id_eliminar);
		const char* i = insert.c_str();
		q_estado = mysql_query(cn.getConectar(), i);
		if (!q_estado) {
			cout << "Eliminado Exitoso" << endl;
		}
		else {
			cout << " xxxx Error al Eliminar xxxx " << endl;

		}
		cn.cerrar_conexion();
	}

	//MODIFICAR
	void modificar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		system("cls");
		string modifica_nit, modifica_nombres, modifica_apellidos, modifica_direccion,  modifica_fecha_nacimiento ;
		int id_modifica, modifica_telefono ;
		string insert;
		cout << "Ingrese Id a modificar: ";
		cin >> id_modifica;
		cout << "Ingrese el nit del cliente: ";
		cin >> modifica_nit ;
		cout << "Ingrese nombres del cliente: ";
		cin >> modifica_nombres; 
		cout << "Ingrese apellidos del cliente: ";
		cin >> modifica_apellidos;
		cout << "Ingrese la direccion del cliente: ";
		cin >> modifica_direccion;
		cout << "Ingrese el telefono del cliente: ";
		cin >> modifica_telefono ;
		cout << "Ingrese la fecha de nacimiento del cliente: ";
		cin >> modifica_fecha_nacimiento;
		insert = "update clientes set nit = '" + modifica_nit + "', nombres = '" + modifica_nombres + "', apellidos = '" + modifica_apellidos + "', direccion='" + modifica_direccion + "', telefono= " + to_string(modifica_telefono) + ",  fecha_nacimiento= '" + modifica_fecha_nacimiento + "' where id_cliente = " + to_string(id_modifica);
		const char* i = insert.c_str();
		q_estado = mysql_query(cn.getConectar(), i);
		if (!q_estado) {
			cout << "Actualizado Exitoso" << endl;
		}
		else {
			cout << " xxxx Error al Actualizar xxxx " << endl;

		}
		cn.cerrar_conexion();
		
	}

	//CREAR
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();
		string t = to_string(telefono);
		if (cn.getConectar()) {
			string  insertar = "INSERT INTO clientes(nit,nombres,apellidos,direccion,telefono,fecha_nacimiento) VALUES ('" + nit + "','" + nombres + "','" + apellidos + "','" + direccion + "'," + t + ",'" + fecha_nacimiento + "')";
			const char* i = insertar.c_str();
			// executar el query
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso ..." << endl;
			}
			else {
				cout << " xxx Error al Ingresar  xxx" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}
	//LEER
	void leer() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {

			cout << "------------ Datos de Clientes ------------" << endl;
			string consulta = "select * from clientes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "," << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4] << "," << fila[5] << "," << fila[6] << endl;
				}

			}
			else {
				cout << " xxx Error al Consultar  xxx" << endl;
			}

		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}
	void menu() {
		int numero;
		do
		{
			system("cls");
			numero = 0;
			cout << "*******\n";
			cout << "                  +------------------------+" << endl;
			cout << "                  |          Menu          |" << endl;
			cout << "                  +------------------------+" << endl;
			cout << "                  | Seleccione una Opcion  |" << endl;
			cout << "                  | 1.- Crear              |" << endl;
			cout << "                  | 2.- Modificar          |" << endl;
			cout << "                  | 3.- Eliminar           |" << endl;
			cout << "                  | 4.- Ver Clientes       |" << endl;
			cout << "                  | 5.- Salir              |" << endl;
			cout << "                  +------------------------+" << endl;
			cout << "*******" << endl;
			cout << "Ingrese un numero ";
			cin >> numero;

			switch (numero) {
			case 1: crear();
				break;
			case 2: modificar();
				break;
			case 3: eliminar();
				break;
			case 4: leer();
				break;
			}
		} while (numero != 5);

	}
	
};