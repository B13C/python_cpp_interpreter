#include <iostream>
#include "Python.h"

using namespace std;

int main()
{
	Py_SetPythonHome(L"./");
	Py_Initialize();

	// Load Python Scripts
	PyObject* PyFileObject = Py_BuildValue("s", "example.py");
	FILE* file = _Py_fopen_obj(PyFileObject, "r+");
	PyRun_SimpleFile(file, "example.py");

	// Load the module
	PyObject* module_name = PyUnicode_FromString("example");
	PyObject* module = PyImport_Import(module_name);
	Py_DECREF(module_name);

	// Get the class definition
	PyObject* class_name = PyUnicode_FromString("ExampleClass");
	PyObject* cls = PyObject_GetAttr(module, class_name);
	Py_DECREF(class_name);

	// Create an instance of the class
	PyObject* instance = PyObject_CallObject(cls, NULL);

	// Call a method on the instance
	PyObject_CallMethod(instance, "example_method", NULL);

	// Clean up
	Py_DECREF(instance);
	Py_DECREF(cls);
	Py_DECREF(module);
	Py_Finalize();
	std::cout << "Hello World!\n";
}
