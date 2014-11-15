#include "Python.h"
#include "gpio_lib.h"


static PyObject *SetupException;
static PyObject *OutputException;
static PyObject *InputException;
static PyObject *inp;
static PyObject *out;
static PyObject *per;
static PyObject *high;
static PyObject *low;

#define PA0    SUNXI_GPA(0)
#define PA1    SUNXI_GPA(1)
#define PA2    SUNXI_GPA(2)
#define PA3    SUNXI_GPA(3)
#define PA4    SUNXI_GPA(4)
#define PA5    SUNXI_GPA(5)
#define PA6    SUNXI_GPA(6)
#define PA7    SUNXI_GPA(7)
#define PA8    SUNXI_GPA(8)
#define PA9    SUNXI_GPA(9)
#define PA10    SUNXI_GPA(10)
#define PA11    SUNXI_GPA(11)
#define PA12    SUNXI_GPA(12)
#define PA13    SUNXI_GPA(13)
#define PA14    SUNXI_GPA(14)
#define PA15    SUNXI_GPA(15)
#define PA16    SUNXI_GPA(16)
#define PA17    SUNXI_GPA(17)

#define PB0    SUNXI_GPB(0)
#define PB1    SUNXI_GPB(1)
#define PB2    SUNXI_GPB(2)
#define PB3    SUNXI_GPB(3)
#define PB4    SUNXI_GPB(4)
#define PB5    SUNXI_GPB(5)
#define PB6    SUNXI_GPB(6)
#define PB7    SUNXI_GPB(7)
#define PB8    SUNXI_GPB(8)
#define PB9    SUNXI_GPB(9)
#define PB10    SUNXI_GPB(10)
#define PB11    SUNXI_GPB(11)
#define PB12    SUNXI_GPB(12)
#define PB13    SUNXI_GPB(13)
#define PB14    SUNXI_GPB(14)
#define PB15    SUNXI_GPB(15)
#define PB16    SUNXI_GPB(16)
#define PB17    SUNXI_GPB(17)
#define PB18    SUNXI_GPB(18)
#define PB19    SUNXI_GPB(19)
#define PB20    SUNXI_GPB(20)
#define PB21    SUNXI_GPB(21)
#define PB22    SUNXI_GPB(22)
#define PB23    SUNXI_GPB(23)

#define PC0    SUNXI_GPC(0)
#define PC1    SUNXI_GPC(1)
#define PC2    SUNXI_GPC(2)
#define PC3    SUNXI_GPC(3)
#define PC4    SUNXI_GPC(4)
#define PC5    SUNXI_GPC(5)
#define PC6    SUNXI_GPC(6)
#define PC7    SUNXI_GPC(7)
#define PC8    SUNXI_GPC(8)
#define PC9    SUNXI_GPC(9)
#define PC10    SUNXI_GPC(10)
#define PC11    SUNXI_GPC(11)
#define PC12    SUNXI_GPC(12)
#define PC13    SUNXI_GPC(13)
#define PC14    SUNXI_GPC(14)
#define PC15    SUNXI_GPC(15)
#define PC16    SUNXI_GPC(16)
#define PC17    SUNXI_GPC(17)
#define PC18    SUNXI_GPC(18)
#define PC19    SUNXI_GPC(19)
#define PC20    SUNXI_GPC(20)
#define PC21    SUNXI_GPC(21)
#define PC22    SUNXI_GPC(22)
#define PC23    SUNXI_GPC(23)
#define PC24    SUNXI_GPC(24)

#define PD0    SUNXI_GPD(0)
#define PD1    SUNXI_GPD(1)
#define PD2    SUNXI_GPD(2)
#define PD3    SUNXI_GPD(3)
#define PD4    SUNXI_GPD(4)
#define PD5    SUNXI_GPD(5)
#define PD6    SUNXI_GPD(6)
#define PD7    SUNXI_GPD(7)
#define PD8    SUNXI_GPD(8)
#define PD9    SUNXI_GPD(9)
#define PD10    SUNXI_GPD(10)
#define PD11    SUNXI_GPD(11)
#define PD12    SUNXI_GPD(12)
#define PD13    SUNXI_GPD(13)
#define PD14    SUNXI_GPD(14)
#define PD15    SUNXI_GPD(15)
#define PD16    SUNXI_GPD(16)
#define PD17    SUNXI_GPD(17)
#define PD18    SUNXI_GPD(18)
#define PD19    SUNXI_GPD(19)
#define PD20    SUNXI_GPD(20)
#define PD21    SUNXI_GPD(21)
#define PD22    SUNXI_GPD(22)
#define PD23    SUNXI_GPD(23)
#define PD24    SUNXI_GPD(24)
#define PD25    SUNXI_GPD(25)
#define PD26    SUNXI_GPD(26)
#define PD27    SUNXI_GPD(27)

#define PE0    SUNXI_GPE(0)
#define PE1    SUNXI_GPE(1)
#define PE2    SUNXI_GPE(2)
#define PE3    SUNXI_GPE(3)
#define PE4    SUNXI_GPE(4)
#define PE5    SUNXI_GPE(5)
#define PE6    SUNXI_GPE(6)
#define PE7    SUNXI_GPE(7)
#define PE8    SUNXI_GPE(8)
#define PE9    SUNXI_GPE(9)
#define PE10    SUNXI_GPE(10)
#define PE11    SUNXI_GPE(11)

#define PF0    SUNXI_GPF(0)
#define PF1    SUNXI_GPF(1)
#define PF2    SUNXI_GPF(2)
#define PF3    SUNXI_GPF(3)
#define PF4    SUNXI_GPF(4)
#define PF5    SUNXI_GPF(5)

#define PG0    SUNXI_GPG(0)
#define PG1    SUNXI_GPG(1)
#define PG2    SUNXI_GPG(2)
#define PG3    SUNXI_GPG(3)
#define PG4    SUNXI_GPG(4)
#define PG5    SUNXI_GPG(5)
#define PG6    SUNXI_GPG(6)
#define PG7    SUNXI_GPG(7)
#define PG8    SUNXI_GPG(8)
#define PG9    SUNXI_GPG(9)
#define PG10    SUNXI_GPG(10)
#define PG11    SUNXI_GPG(11)

#define PH0    SUNXI_GPH(0)
#define PH1    SUNXI_GPH(1)
#define PH2    SUNXI_GPH(2)
#define PH3    SUNXI_GPH(3)
#define PH4    SUNXI_GPH(4)
#define PH5    SUNXI_GPH(5)
#define PH6    SUNXI_GPH(6)
#define PH7    SUNXI_GPH(7)
#define PH8    SUNXI_GPH(8)
#define PH9    SUNXI_GPH(9)
#define PH10    SUNXI_GPH(10)
#define PH11    SUNXI_GPH(11)
#define PH12    SUNXI_GPH(12)
#define PH13    SUNXI_GPH(13)
#define PH14    SUNXI_GPH(14)
#define PH15    SUNXI_GPH(15)
#define PH16    SUNXI_GPH(16)
#define PH17    SUNXI_GPH(17)
#define PH18    SUNXI_GPH(18)
#define PH19    SUNXI_GPH(19)
#define PH20    SUNXI_GPH(20)
#define PH21    SUNXI_GPH(21)
#define PH22    SUNXI_GPH(22)
#define PH23    SUNXI_GPH(23)
#define PH24    SUNXI_GPH(24)
#define PH25    SUNXI_GPH(25)
#define PH26    SUNXI_GPH(26)
#define PH27    SUNXI_GPH(27)

#define PI0    SUNXI_GPI(0)
#define PI1    SUNXI_GPI(1)
#define PI2    SUNXI_GPI(2)
#define PI3    SUNXI_GPI(3)
#define PI4    SUNXI_GPI(4)
#define PI5    SUNXI_GPI(5)
#define PI6    SUNXI_GPI(6)
#define PI7    SUNXI_GPI(7)
#define PI8    SUNXI_GPI(8)
#define PI9    SUNXI_GPI(9)
#define PI10    SUNXI_GPI(10)
#define PI11    SUNXI_GPI(11)
#define PI12    SUNXI_GPI(12)
#define PI13    SUNXI_GPI(13)
#define PI14    SUNXI_GPI(14)
#define PI15    SUNXI_GPI(15)
#define PI16    SUNXI_GPI(16)
#define PI17    SUNXI_GPI(17)
#define PI18    SUNXI_GPI(18)
#define PI19    SUNXI_GPI(19)
#define PI20    SUNXI_GPI(20)
#define PI21    SUNXI_GPI(21)

static int module_setup(void) {
    int result;

    result = sunxi_gpio_init();
    if(result == SETUP_DEVMEM_FAIL) {
        PyErr_SetString(SetupException, "No access to /dev/mem. Try running as root!");
        return SETUP_DEVMEM_FAIL;
    }
    else if(result == SETUP_MALLOC_FAIL) {
        PyErr_NoMemory();
        return SETUP_MALLOC_FAIL;
    }
    else if(result == SETUP_MMAP_FAIL) {
        PyErr_SetString(SetupException, "Mmap failed on module import");
        return SETUP_MMAP_FAIL;
    }
    else {
        return SETUP_OK;
    }

    return SETUP_OK;
}






static PyObject* py_output(PyObject* self, PyObject* args) {
    int gpio;
    int value;

    if(!PyArg_ParseTuple(args, "ii", &gpio, &value))
        return NULL;

    if(value != 0 && value != 1) {
        PyErr_SetString(OutputException, "Invalid output state");
        return NULL;
    }

    if(sunxi_gpio_get_cfgpin(gpio) != SUNXI_GPIO_OUTPUT) {
        PyErr_SetString(OutputException, "GPIO is no an output");
        return NULL;
    }
    sunxi_gpio_output(gpio, value);

    Py_RETURN_NONE;
}
static PyObject* py_input(PyObject* self, PyObject* args) {
    int gpio;
    int result;

    if(!PyArg_ParseTuple(args, "i", &gpio))
        return NULL;

    if(sunxi_gpio_get_cfgpin(gpio) != SUNXI_GPIO_INPUT) {
        PyErr_SetString(InputException, "GPIO is not an input");
        return NULL;
    }
    result = sunxi_gpio_input(gpio);

    if(result == -1) {
        PyErr_SetString(InputException, "Reading pin failed");
        return NULL;
    }


    return Py_BuildValue("i", result);
}

static PyObject* py_setcfg(PyObject* self, PyObject* args) {
    int gpio;
    int direction;

    if(!PyArg_ParseTuple(args, "ii", &gpio, &direction))
        return NULL;

    if(direction != 0 && direction != 1 && direction != 2) {
        PyErr_SetString(SetupException, "Invalid direction");
        return NULL;
    }
    sunxi_gpio_set_cfgpin(gpio, direction);

    Py_RETURN_NONE;
}
static PyObject* py_getcfg(PyObject* self, PyObject* args) {
    int gpio;
    int result;


    if(!PyArg_ParseTuple(args, "i", &gpio))
        return NULL;

    result = sunxi_gpio_get_cfgpin(gpio);


    return Py_BuildValue("i", result);


}
static PyObject* py_init(PyObject* self, PyObject* args) {

    module_setup();

    Py_RETURN_NONE;
}
static PyObject* py_cleanup(PyObject* self, PyObject* args) {

    sunxi_gpio_cleanup();
    Py_RETURN_NONE;
}


PyMethodDef module_methods[] = {
    {"init", py_init, METH_NOARGS, "Initialize module"},
    {"cleanup", py_cleanup, METH_NOARGS, "munmap /dev/map."},
    {"setcfg", py_setcfg, METH_VARARGS, "Set direction."},
    {"getcfg", py_getcfg, METH_VARARGS, "Get direction."},
    {"output", py_output, METH_VARARGS, "Set output state"},
    {"input", py_input, METH_VARARGS, "Get input state"},
    {NULL, NULL, 0, NULL}
};
#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "SUNXI module",
    NULL,
    -1,
    module_methods
};
#endif
PyMODINIT_FUNC initSUNXI_GPIO(void) {
    PyObject* module = NULL;


#if PY_MAJOR_VERSION >= 3
    module = PyModule_Create(&module_methods);
#else
    module = Py_InitModule("SUNXI_GPIO", module_methods);
#endif


    if(module == NULL)
#if PY_MAJOR_VERSION >= 3
        return module;
#else
        return;
#endif



    SetupException = PyErr_NewException("PySUNXI.SetupException", NULL, NULL);
    PyModule_AddObject(module, "SetupException", SetupException);
    OutputException = PyErr_NewException("PySUNXI.OutputException", NULL, NULL);
    PyModule_AddObject(module, "OutputException", OutputException);
    InputException = PyErr_NewException("PySUNXI.InputException", NULL, NULL);
    PyModule_AddObject(module, "InputException", InputException);



    high = Py_BuildValue("i", HIGH);
    PyModule_AddObject(module, "HIGH", high);

    low = Py_BuildValue("i", LOW);
    PyModule_AddObject(module, "LOW", low);

    inp = Py_BuildValue("i", INPUT);
    PyModule_AddObject(module, "IN", inp);

    out = Py_BuildValue("i", OUTPUT);
    PyModule_AddObject(module, "OUT", out);

    per = Py_BuildValue("i", PER);
    PyModule_AddObject(module, "PER", per);


    PyModule_AddObject(module, "PA0", Py_BuildValue("i", PA0));
    PyModule_AddObject(module, "PA1", Py_BuildValue("i", PA1));
    PyModule_AddObject(module, "PA2", Py_BuildValue("i", PA2));
    PyModule_AddObject(module, "PA3", Py_BuildValue("i", PA3));
    PyModule_AddObject(module, "PA4", Py_BuildValue("i", PA4));
    PyModule_AddObject(module, "PA5", Py_BuildValue("i", PA5));
    PyModule_AddObject(module, "PA6", Py_BuildValue("i", PA6));
    PyModule_AddObject(module, "PA7", Py_BuildValue("i", PA7));
    PyModule_AddObject(module, "PA8", Py_BuildValue("i", PA8));
    PyModule_AddObject(module, "PA9", Py_BuildValue("i", PA9));
    PyModule_AddObject(module, "PA10", Py_BuildValue("i", PA10));
    PyModule_AddObject(module, "PA11", Py_BuildValue("i", PA11));
    PyModule_AddObject(module, "PA12", Py_BuildValue("i", PA12));
    PyModule_AddObject(module, "PA13", Py_BuildValue("i", PA13));
    PyModule_AddObject(module, "PA14", Py_BuildValue("i", PA14));
    PyModule_AddObject(module, "PA15", Py_BuildValue("i", PA15));
    PyModule_AddObject(module, "PA16", Py_BuildValue("i", PA16));
    PyModule_AddObject(module, "PA17", Py_BuildValue("i", PA17));

    PyModule_AddObject(module, "PB0", Py_BuildValue("i", PB0));
    PyModule_AddObject(module, "PB1", Py_BuildValue("i", PB1));
    PyModule_AddObject(module, "PB2", Py_BuildValue("i", PB2));
    PyModule_AddObject(module, "PB3", Py_BuildValue("i", PB3));
    PyModule_AddObject(module, "PB4", Py_BuildValue("i", PB4));
    PyModule_AddObject(module, "PB5", Py_BuildValue("i", PB5));
    PyModule_AddObject(module, "PB6", Py_BuildValue("i", PB6));
    PyModule_AddObject(module, "PB7", Py_BuildValue("i", PB7));
    PyModule_AddObject(module, "PB8", Py_BuildValue("i", PB8));
    PyModule_AddObject(module, "PB9", Py_BuildValue("i", PB9));
    PyModule_AddObject(module, "PB10", Py_BuildValue("i", PB10));
    PyModule_AddObject(module, "PB11", Py_BuildValue("i", PB11));
    PyModule_AddObject(module, "PB12", Py_BuildValue("i", PB12));
    PyModule_AddObject(module, "PB13", Py_BuildValue("i", PB13));
    PyModule_AddObject(module, "PB14", Py_BuildValue("i", PB14));
    PyModule_AddObject(module, "PB15", Py_BuildValue("i", PB15));
    PyModule_AddObject(module, "PB16", Py_BuildValue("i", PB16));
    PyModule_AddObject(module, "PB17", Py_BuildValue("i", PB17));
    PyModule_AddObject(module, "PB18", Py_BuildValue("i", PB18));
    PyModule_AddObject(module, "PB19", Py_BuildValue("i", PB19));
    PyModule_AddObject(module, "PB20", Py_BuildValue("i", PB20));
    PyModule_AddObject(module, "PB21", Py_BuildValue("i", PB21));
    PyModule_AddObject(module, "PB22", Py_BuildValue("i", PB22));
    PyModule_AddObject(module, "PB23", Py_BuildValue("i", PB23));

    PyModule_AddObject(module, "PC0", Py_BuildValue("i", PC0));
    PyModule_AddObject(module, "PC1", Py_BuildValue("i", PC1));
    PyModule_AddObject(module, "PC2", Py_BuildValue("i", PC2));
    PyModule_AddObject(module, "PC3", Py_BuildValue("i", PC3));
    PyModule_AddObject(module, "PC4", Py_BuildValue("i", PC4));
    PyModule_AddObject(module, "PC5", Py_BuildValue("i", PC5));
    PyModule_AddObject(module, "PC6", Py_BuildValue("i", PC6));
    PyModule_AddObject(module, "PC7", Py_BuildValue("i", PC7));
    PyModule_AddObject(module, "PC8", Py_BuildValue("i", PC8));
    PyModule_AddObject(module, "PC9", Py_BuildValue("i", PC9));
    PyModule_AddObject(module, "PC10", Py_BuildValue("i", PC10));
    PyModule_AddObject(module, "PC11", Py_BuildValue("i", PC11));
    PyModule_AddObject(module, "PC12", Py_BuildValue("i", PC12));
    PyModule_AddObject(module, "PC13", Py_BuildValue("i", PC13));
    PyModule_AddObject(module, "PC14", Py_BuildValue("i", PC14));
    PyModule_AddObject(module, "PC15", Py_BuildValue("i", PC15));
    PyModule_AddObject(module, "PC16", Py_BuildValue("i", PC16));
    PyModule_AddObject(module, "PC17", Py_BuildValue("i", PC17));
    PyModule_AddObject(module, "PC18", Py_BuildValue("i", PC18));
    PyModule_AddObject(module, "PC19", Py_BuildValue("i", PC19));
    PyModule_AddObject(module, "PC20", Py_BuildValue("i", PC20));
    PyModule_AddObject(module, "PC21", Py_BuildValue("i", PC21));
    PyModule_AddObject(module, "PC22", Py_BuildValue("i", PC22));
    PyModule_AddObject(module, "PC23", Py_BuildValue("i", PC23));
    PyModule_AddObject(module, "PC24", Py_BuildValue("i", PC24));

    PyModule_AddObject(module, "PD0", Py_BuildValue("i", PD0));
    PyModule_AddObject(module, "PD1", Py_BuildValue("i", PD1));
    PyModule_AddObject(module, "PD2", Py_BuildValue("i", PD2));
    PyModule_AddObject(module, "PD3", Py_BuildValue("i", PD3));
    PyModule_AddObject(module, "PD4", Py_BuildValue("i", PD4));
    PyModule_AddObject(module, "PD5", Py_BuildValue("i", PD5));
    PyModule_AddObject(module, "PD6", Py_BuildValue("i", PD6));
    PyModule_AddObject(module, "PD7", Py_BuildValue("i", PD7));
    PyModule_AddObject(module, "PD8", Py_BuildValue("i", PD8));
    PyModule_AddObject(module, "PD9", Py_BuildValue("i", PD9));
    PyModule_AddObject(module, "PD10", Py_BuildValue("i", PD10));
    PyModule_AddObject(module, "PD11", Py_BuildValue("i", PD11));
    PyModule_AddObject(module, "PD12", Py_BuildValue("i", PD12));
    PyModule_AddObject(module, "PD13", Py_BuildValue("i", PD13));
    PyModule_AddObject(module, "PD14", Py_BuildValue("i", PD14));
    PyModule_AddObject(module, "PD15", Py_BuildValue("i", PD15));
    PyModule_AddObject(module, "PD16", Py_BuildValue("i", PD16));
    PyModule_AddObject(module, "PD17", Py_BuildValue("i", PD17));
    PyModule_AddObject(module, "PD18", Py_BuildValue("i", PD18));
    PyModule_AddObject(module, "PD19", Py_BuildValue("i", PD19));
    PyModule_AddObject(module, "PD20", Py_BuildValue("i", PD20));
    PyModule_AddObject(module, "PD21", Py_BuildValue("i", PD21));
    PyModule_AddObject(module, "PD22", Py_BuildValue("i", PD22));
    PyModule_AddObject(module, "PD23", Py_BuildValue("i", PD23));
    PyModule_AddObject(module, "PD24", Py_BuildValue("i", PD24));
    PyModule_AddObject(module, "PD25", Py_BuildValue("i", PD25));
    PyModule_AddObject(module, "PD26", Py_BuildValue("i", PD26));
    PyModule_AddObject(module, "PD27", Py_BuildValue("i", PD27));

    PyModule_AddObject(module, "PE0", Py_BuildValue("i", PE0));
    PyModule_AddObject(module, "PE1", Py_BuildValue("i", PE1));
    PyModule_AddObject(module, "PE2", Py_BuildValue("i", PE2));
    PyModule_AddObject(module, "PE3", Py_BuildValue("i", PE3));
    PyModule_AddObject(module, "PE4", Py_BuildValue("i", PE4));
    PyModule_AddObject(module, "PE5", Py_BuildValue("i", PE5));
    PyModule_AddObject(module, "PE6", Py_BuildValue("i", PE6));
    PyModule_AddObject(module, "PE7", Py_BuildValue("i", PE7));
    PyModule_AddObject(module, "PE8", Py_BuildValue("i", PE8));
    PyModule_AddObject(module, "PE9", Py_BuildValue("i", PE9));
    PyModule_AddObject(module, "PE10", Py_BuildValue("i", PE10));
    PyModule_AddObject(module, "PE11", Py_BuildValue("i", PE11));

    PyModule_AddObject(module, "PF0", Py_BuildValue("i", PF0));
    PyModule_AddObject(module, "PF1", Py_BuildValue("i", PF1));
    PyModule_AddObject(module, "PF2", Py_BuildValue("i", PF2));
    PyModule_AddObject(module, "PF3", Py_BuildValue("i", PF3));
    PyModule_AddObject(module, "PF4", Py_BuildValue("i", PF4));
    PyModule_AddObject(module, "PF5", Py_BuildValue("i", PF5));

    PyModule_AddObject(module, "PG0", Py_BuildValue("i", PG0));
    PyModule_AddObject(module, "PG1", Py_BuildValue("i", PG1));
    PyModule_AddObject(module, "PG2", Py_BuildValue("i", PG2));
    PyModule_AddObject(module, "PG3", Py_BuildValue("i", PG3));
    PyModule_AddObject(module, "PG4", Py_BuildValue("i", PG4));
    PyModule_AddObject(module, "PG5", Py_BuildValue("i", PG5));
    PyModule_AddObject(module, "PG6", Py_BuildValue("i", PG6));
    PyModule_AddObject(module, "PG7", Py_BuildValue("i", PG7));
    PyModule_AddObject(module, "PG8", Py_BuildValue("i", PG8));
    PyModule_AddObject(module, "PG9", Py_BuildValue("i", PG9));
    PyModule_AddObject(module, "PG10", Py_BuildValue("i", PG10));
    PyModule_AddObject(module, "PG11", Py_BuildValue("i", PG11));

    PyModule_AddObject(module, "PH0", Py_BuildValue("i", PH0));
    PyModule_AddObject(module, "PH1", Py_BuildValue("i", PH1));
    PyModule_AddObject(module, "PH2", Py_BuildValue("i", PH2));
    PyModule_AddObject(module, "PH3", Py_BuildValue("i", PH3));
    PyModule_AddObject(module, "PH4", Py_BuildValue("i", PH4));
    PyModule_AddObject(module, "PH5", Py_BuildValue("i", PH5));
    PyModule_AddObject(module, "PH6", Py_BuildValue("i", PH6));
    PyModule_AddObject(module, "PH7", Py_BuildValue("i", PH7));
    PyModule_AddObject(module, "PH8", Py_BuildValue("i", PH8));
    PyModule_AddObject(module, "PH9", Py_BuildValue("i", PH9));
    PyModule_AddObject(module, "PH10", Py_BuildValue("i", PH10));
    PyModule_AddObject(module, "PH11", Py_BuildValue("i", PH11));
    PyModule_AddObject(module, "PH12", Py_BuildValue("i", PH12));
    PyModule_AddObject(module, "PH13", Py_BuildValue("i", PH13));
    PyModule_AddObject(module, "PH14", Py_BuildValue("i", PH14));
    PyModule_AddObject(module, "PH15", Py_BuildValue("i", PH15));
    PyModule_AddObject(module, "PH16", Py_BuildValue("i", PH16));
    PyModule_AddObject(module, "PH17", Py_BuildValue("i", PH17));
    PyModule_AddObject(module, "PH18", Py_BuildValue("i", PH18));
    PyModule_AddObject(module, "PH19", Py_BuildValue("i", PH19));
    PyModule_AddObject(module, "PH20", Py_BuildValue("i", PH20));
    PyModule_AddObject(module, "PH21", Py_BuildValue("i", PH21));
    PyModule_AddObject(module, "PH22", Py_BuildValue("i", PH22));
    PyModule_AddObject(module, "PH23", Py_BuildValue("i", PH23));
    PyModule_AddObject(module, "PH24", Py_BuildValue("i", PH24));
    PyModule_AddObject(module, "PH25", Py_BuildValue("i", PH25));
    PyModule_AddObject(module, "PH26", Py_BuildValue("i", PH26));
    PyModule_AddObject(module, "PH27", Py_BuildValue("i", PH27));

    PyModule_AddObject(module, "PI0", Py_BuildValue("i", PI0));
    PyModule_AddObject(module, "PI1", Py_BuildValue("i", PI1));
    PyModule_AddObject(module, "PI2", Py_BuildValue("i", PI2));
    PyModule_AddObject(module, "PI3", Py_BuildValue("i", PI3));
    PyModule_AddObject(module, "PI4", Py_BuildValue("i", PI4));
    PyModule_AddObject(module, "PI5", Py_BuildValue("i", PI5));
    PyModule_AddObject(module, "PI6", Py_BuildValue("i", PI6));
    PyModule_AddObject(module, "PI7", Py_BuildValue("i", PI7));
    PyModule_AddObject(module, "PI8", Py_BuildValue("i", PI8));
    PyModule_AddObject(module, "PI9", Py_BuildValue("i", PI9));
    PyModule_AddObject(module, "PI10", Py_BuildValue("i", PI10));
    PyModule_AddObject(module, "PI11", Py_BuildValue("i", PI11));
    PyModule_AddObject(module, "PI12", Py_BuildValue("i", PI12));
    PyModule_AddObject(module, "PI13", Py_BuildValue("i", PI13));
    PyModule_AddObject(module, "PI14", Py_BuildValue("i", PI14));
    PyModule_AddObject(module, "PI15", Py_BuildValue("i", PI15));
    PyModule_AddObject(module, "PI16", Py_BuildValue("i", PI16));
    PyModule_AddObject(module, "PI17", Py_BuildValue("i", PI17));
    PyModule_AddObject(module, "PI18", Py_BuildValue("i", PI18));
    PyModule_AddObject(module, "PI19", Py_BuildValue("i", PI19));
    PyModule_AddObject(module, "PI20", Py_BuildValue("i", PI20));
    PyModule_AddObject(module, "PI21", Py_BuildValue("i", PI21));
    
    if(Py_AtExit(sunxi_gpio_cleanup) != 0){
        
        sunxi_gpio_cleanup();
        
#if PY_MAJOR_VERSION >= 3
        return NULL;
#else
        return;
#endif
    }

}

