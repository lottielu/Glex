
#include <boost/python.hpp>
#include "GameAssetManager.h"
#include "GameWorld.h"
#include "Common.h"

usng namespace boost::python;

PythonBindings::PythonBindings()
{
}

BOOST_PYTHON_MODULE(glex){

	class<GameWorld>("GameWorld").def("LibBindTest",&GameWorld::LibBindTest)

}
