
#include "ip_rec.h"


rec::rec(ip_rec _rec_1) : rec_1(_rec_1) {}

bool rec::operator< (const rec& rec_2) const
{
	auto it_1 = rec_1.cbegin();
	auto it_2 = rec_2.rec_1.cbegin();

	while( it_1 != rec_1.cend()) { //rec_1.size == rec_2.size
		if ( stoul(*it_1) ==  stoul(*it_2) ) {
			++it_2;
			++it_1;
		}    
		else   
			return (stoul(*it_1) <  stoul(*it_2));
	}
	return false;
}


size_t rec::size() {
	return rec_1.size();
}
