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
#include "ns3/ipv4-global-routing-helper.h" // Guillaume, si tu veux, on peut chercher pour ipv6 :)

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Simple Topologie");

int main() {
	// print messages
	LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  	NS_LOG_INFO ("Creating Topology");

  	// create node containers and their nodes
  	NodeContainer firstPair;
  	NodeContainer secondPair;
  	NodeContainer thirdPair;
  	NodeContainer clients;
  	NodeContainer all;
  	// Node n0 will be the common node for all pairs
  	firstPair.Create(2);
  	secondPair.Add(firstPair.Get(0));
  	secondPair.Create(1);
  	thirdPair.Add(firstPair.Get(0));
  	thirdPair.Create(1);
  	clients.Add(firstPair.Get(1));
  	clients.Add(secondPair.Get(1));
	clients.Add(thirdPair.Get(1));
	all.Add(firstPair.Get(0));
	all.Add(clients);

  	// set point-to-point connections
  	PointToPointHelper pointToPoint;
  	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  	// set net devices
  	NetDeviceContainer P2pDevices;
  	// TODO MUDAR AQUI
  	P2pDevices = pointToPoint.Install (all);

  	// set internet stack
  	InternetStackHelper stack;
  	stack.Install (firstPair);
  	stack.Install (secondPair.Get(1));
  	stack.Install (thirdPair.Get(1));

  	// set ip adresses
  	Ipv4AddressHelper address;
  	address.SetBase ("10.1.1.0", "255.255.255.0");
  	Ipv4InterfaceContainer p2pInterfaces;
  	p2pInterfaces = address.Assign(P2pDevices);

  	// server settings
  	UdpEchoServerHelper echoServer (9);
  	ApplicationContainer serverApps = echoServer.Install (firstPair.Get(0));
  	serverApps.Start (Seconds (1.0));
  	serverApps.Stop (Seconds (10.0));

  	// client settings
  	UdpEchoClientHelper echoClient (p2pInterfaces.GetAddress(0), 9);
  	echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
  	// install clients
  	ApplicationContainer clientApps = echoClient.Install(clients);
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));

  	// routing table
  	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  	Simulator::Run ();
  	Simulator::Destroy ();
  	return 0;
}