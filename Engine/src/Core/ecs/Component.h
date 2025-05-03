#pragma once

namespace hydro::ecs
{
	struct IComponent
	{
	public:
		virtual ~IComponent() = default;
	};

	class IScript : public IComponent
	{
	public:
		virtual ~IScript() = default;
		virtual void Start() = 0;
		virtual void Update() = 0;
	};
}