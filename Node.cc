/* author: Carolina de Senne Garcia <desennecarol@gmail.com>
 * BIER Forwarding Router (Node instances)
 */

using namespace ns3;
#include <queue>
#include <condition_variable>
// MAKE IT THREAD SAFE ???

#include <vector>
#define WINDOW_SIZE (10)

class Router {

	vector<Router> neighbours;
	queue<BierPacket> packets;

	// send a packet to the destination Node
	void send(BierPacket p, Router destination) {

	}

	// receives a packet and enqueues it
	// returns 0 if there was space in the queue and 1 if not
	int receive(BierPacket p) {
		// check if this packet is for me
		// TODO
		// if it is not for me, put in the queue to treat later
		if(packets.size() < WINDOW_SIZE) {
			packets.push(p);
		}
	}

	// forwards the packet throw the right interface
	void forward() {

	}

}