
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
			if(!this->tunnel[idx].active ) {continue;}
			if((this->tunnel[idx].begin) > this->ctunnel){continue;} 
			if(this-> tunnel[idx].end != 0 && this->tunnel[idx].total>=this->tunnel[idx].end) {
				this->tunnel[idx].active=false;
				this->tunnel[idx].tlfunc = nullptr;
				continue;
			} 
		    auto tls =  this->tunnel[idx].tlfunc;
		    tls(this->data);
		    this->tunnel[idx].active = true;
		    this->tunnel[idx].total++;

		}
	}
	void collect(const std::function<void(const T&)> &cF, 
	    std::uint16_t bg=0, std::uint16_t end=0) {	    
		this->ctunnel = (std::uint16_t)(this->tunnel.size());
		this->tunnel.emplace_back(TunnelInfo{cF, bg, end, 0,true});
		
	}

		
};
}
#endif

