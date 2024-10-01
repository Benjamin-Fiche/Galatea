#pragma once

#include <iostream>

namespace UserFileAdder
{
	static std::string CreateNewComponentClass(std::string name)
	{
		std::string componentClass =
									"#pragma once\n"
									"\n"
									"#include <ComponentSystem/Component.h>\n"
									"#include \"rttr/registration_friend.h\"\n"
									"\n"
									"using namespace Galatea;\n"
									"\n"
									"class ";
		componentClass +=			name;
		componentClass +=			" : public Component\n"
									"{\n"
									"public:\n"
									"\t"; 
		componentClass +=			name;
		componentClass +=			"() = default;\n"
									"\t~";
		componentClass +=			name;
		componentClass +=			"() = default;\n"
									"\n"
									"\tRTTR_ENABLE(Component)\n"
									"\tRTTR_REGISTRATION_FRIEND\n"
									"};\n"
									"\n"
									"//To add reflection correctly refer to MyComponent.h in the User Solution\n";

		return componentClass;
	}

	static std::string CreateNewUpdatableComponentClass(std::string name)
	{
		std::string componentClass =
									"#pragma once\n"
									"\n"
									"#include <ComponentSystem/UpdatableComponent.h>\n"
									"#include \"rttr/registration_friend.h\"\n"
									"\n"
									"using namespace Galatea;\n"
									"\n"
									"class ";
		componentClass +=			name;
		componentClass +=			" : public UpdatableComponent\n"
									"{\n"
									"public:\n"
									"\t";
		componentClass +=			name;
		componentClass +=			"() = default;\n"
									"\t~";
		componentClass +=			name;
		componentClass +=			"() = default;\n"
									"\n"
									"\tRTTR_ENABLE(UpdatableComponent)\n"
									"\tRTTR_REGISTRATION_FRIEND\n"
									"};\n"
									"\n"
									"//To add reflection correctly refer to MyComponent.h in the User Solution\n";

		return componentClass;
	}
}