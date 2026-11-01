

#ifndef Flow_H
#define Flow_H

#include <functional>
#include <vector>
#include <cstdint>

namespace Tunnel {
template <typename T>
class Flow {
private:
	struct TunnelInfo{
		std::function<void(const T&)> tlfunc;
		std::uint16_t begin;
		std::uint16_t end;
		std::uint16_t total;
		bool active;		
	};
	T data;
	std::uint16_t ctunnel =0;
	std::vector<TunnelInfo> tunnel;
public:
	Flow(T fT) : data(std::move(fT)) {}
	
	
	void update(const std::function<T(const T&)> &uF) {
		this->data = std::move(uF(this->data));
		std::size_t ts =this->tunnel.size();
		for(std::size_t idx=0; idx <ts; idx++) {
			auto &tls =  this->tunnel[idx];
			if(!tls.active ) {continue;}

			if((tls.begin) > this->ctunnel){continue;} 
			if(tls.end != 0 && tls.total>=tls.end) {
				tls.active=false;
				tls.tlfunc = nullptr;
				continue;
			} else {
				tls.tlfunc(this->data);
				tls.total=(std::uint16_t)(tls.total+1);
				tls.active=true;
			}
		}
	}
	void collect(const std::function<void(const T&)> &cF, std::uint16_t bg=0, std::uint16_t end=0) {
		
		    
		this->ctunnel = (std::uint16_t)(this->tunnel.size());
		this->tunnel.emplace_back(TunnelInfo{cF, bg, end, 0,true});
		
	}
		
};
}
#endif

