#pragma once

namespace hydro::gfx
{
	class Bindable {
	public:
		virtual void Bind() = 0;
		virtual ~Bindable() = default;
	};
}