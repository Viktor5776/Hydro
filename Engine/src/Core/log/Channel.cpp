#include "Channel.h"
#include "Driver.h"

namespace hydro::log
{

	Channel::Channel( std::vector<std::shared_ptr<IDriver>> driverPtrs )
		:
		driverPtrs_( std::move(driverPtrs) )
	{}

	void Channel::Submit( Entry& entry )
	{
		for( auto& pDriver : driverPtrs_ )
		{
			pDriver->Submit( entry );
		}
	}

	void Channel::AttachDriver( std::shared_ptr<IDriver> pDriver )
	{
		driverPtrs_.push_back( std::move( pDriver ) );
	}

}