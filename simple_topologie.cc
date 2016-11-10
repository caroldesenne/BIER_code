/* 
	author: Carolina de Senne Garcia

	Node n0 = server
	Nodes n1,n2,3 = clients
	Server and clients are connected by a point-to-point connection
	The clients ask the server to send it messages, the server sends periodically BIER messages to the clients

	  Network Topology:
	  
		 --- n0 ---
		|    |	  |
		n1	 n2   n3

*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Simple Topologie");

int main() {
	// print messages
	LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  	NS_LOG_INFO ("Creating Topology");
}