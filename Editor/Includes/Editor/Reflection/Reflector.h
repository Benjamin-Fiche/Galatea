#pragma once

#include "Core/ReflectionRegistration.h"
#include "Editor/OnInspectorUI.h"
#include "Maths/Vec3.h"
#include "Maths/Quaternion.h"
#include "Debug/Log.h"

namespace Galatea
{
	class Reflector
	{
	public:
		static void ManageSequentialView(rttr::variant_sequential_view& view) noexcept
		{
			for (int i = 0; i < view.get_size(); ++i)
			{
				rttr::string_view tName = view.get_value(i).extract_wrapped_value().get_type().get_name();
				
				if (ImGui::TreeNodeEx(tName.data(), ImGuiTreeNodeFlags_Framed))
				{
					if (tName == "bool")
					{
						bool value = view.get_value(i).extract_wrapped_value().to_bool();
						Galatea::OnInspectorUI::DragValue(std::to_string(i).c_str(), &value);
						view.set_value(i, value);
					}
					else if (tName == "double")
					{
						double value = view.get_value(i).extract_wrapped_value().to_double();
						Galatea::OnInspectorUI::DragValue(std::to_string(i).c_str(), &value);
						view.set_value(i, value);
					}
					else if (tName == "float")
					{
						float value = view.get_value(i).extract_wrapped_value().to_float();
						Galatea::OnInspectorUI::DragValue(std::to_string(i).c_str(), &value);
						view.set_value(i, value);
					}
					else if (tName == "int")
					{
						int value = view.get_value(i).extract_wrapped_value().to_int();
						Galatea::OnInspectorUI::DragValue(std::to_string(i).c_str(), &value);
						view.set_value(i, value);
					}
					else if (tName == "uint32_t")
					{
						unsigned int value = view.get_value(i).extract_wrapped_value().to_uint32();
						Galatea::OnInspectorUI::DragValue(std::to_string(i).c_str(), &value);
						view.set_value(i, value);
					}
					else if (tName == "std::string")
						ImGui::Text(view.get_value(i).extract_wrapped_value().to_string().c_str());
					else
					{
						variant var = view.get_value(i).extract_wrapped_value();
						if (var.is_sequential_container())
						{
							variant_sequential_view view = var.create_sequential_view();
							Reflector::ManageSequentialView(view);
							view.set_value(i, var);
						}
						else
							view.set_value(i, Reflector::RttrLoop(view.get_value(i).extract_wrapped_value().get_type(), view.get_value(i).extract_wrapped_value()));
					}
					ImGui::TreePop();
				}
			}
		}

		// On parcourt les properties et si elle ne sont pas du type base on relance la boucle 
		template<class T>
		static T RttrLoop(const rttr::type& t, const T& object) noexcept
		{
			if (t.get_properties().size() > 0 && ImGui::TreeNodeEx(t.get_name().data(), ImGuiTreeNodeFlags_Framed)) //create a node in ImGui
			{
				for (auto prop : t.get_properties())
				{
					rttr::string_view typeName = prop.get_type().get_name();

					//Comparing type of the property to base type to reflect it
					if (typeName == "bool")
					{
						bool value = prop.get_value(object).to_bool();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);
						
						if (prop.get_value(object).to_bool() != value)
							prop.set_value(object, value);
					}
					else if (typeName == "double")
					{
						double value = prop.get_value(object).to_double();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);

						if (prop.get_value(object).to_double() != value)
							prop.set_value(object, value);
					}
					else if (typeName == "float")
					{
						float value = prop.get_value(object).to_float();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);

						if (prop.get_value(object).to_float() != value)
							prop.set_value(object, value);
					}
					else if (typeName == "int")
					{
						int value = prop.get_value(object).to_int();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);

						if (prop.get_value(object).to_int() != value)
							prop.set_value(object, value);
					}
					else if (typeName == "uint32_t")
					{
						unsigned int value = prop.get_value(object).to_uint32();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);

						if (prop.get_value(object).to_uint32() != value)
							prop.set_value(object, value);
					}
					else if (typeName == "std::string") //cannot be changed because it's a const char*
						ImGui::Text((prop.get_name() + std::string(" : ") + prop.get_value(object).to_string()).c_str());
					else if (typeName == "Vec3")
					{
						Vec3 value = prop.get_value(object).get_value<Vec3>();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);

						if (!(value == (Vec3)prop.get_value(object).get_value<Vec3>()))
							prop.set_value(object, value);
					}
					else if (typeName == "Quaternion")
					{
						Quaternion value = prop.get_value(object).get_value<Quaternion>();
						Galatea::OnInspectorUI::DragValue(prop.get_name().data(), &value);

						if (!(value == (Quaternion)prop.get_value(object).get_value<Quaternion>()))
							prop.set_value(object, value);
					}
					else if (!prop.get_type().is_enumeration())
					{
						rttr::variant var = prop.get_value(object);
						if (var.is_sequential_container())
						{
							variant_sequential_view view = var.create_sequential_view();
							Reflector::ManageSequentialView(view);
							prop.set_value(object, var);
						}
						else
							prop.set_value(object, Reflector::RttrLoop(prop.get_type(), prop.get_value(object)));
					}
				}
				ImGui::TreePop(); // close ImGui node
			}
			return object;
		}

		//Only work with object nothing happends if you pass a base type as an object
		template<class T>
		static void Reflect(T* object)
		{
			type t = type::get(*object);

			Reflector::RttrLoop(t, *object);
		}
	};
}