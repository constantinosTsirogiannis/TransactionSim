#ifndef NETWORK_TYPES_H
#define NETWORK_TYPES_H

#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<algorithm>

#include <boost/random.hpp>
#include<boost/random/uniform_real.hpp>
#include<boost/lexical_cast.hpp>


#include<CGAL/Random.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>





struct Node_type
{
  std::string name, place;
  double longitude, latitude;
  int active_since, active_until, serial_number;
  int mark;
 
  struct Edge_type
  {
    int from,to,weight;
  
    Edge_type():from(0),to(0),weight(0)
    {}
  };

  std::vector<Edge_type> in_edges, out_edges;


  Node_type(): longitude(-1), latitude(-1), 
               active_since(-1), active_until(-2), serial_number(-1), mark(-1)
  {}

  bool was_active( int t )
  { return ( t>= (active_since-2) && t<= active_until && active_since <= active_until );  }

  bool was_active( int t1, int t2 )
  { 
     return ( !( t2< (active_since-2) || t1> active_until ) 
             && t1<=t2 && active_since <= active_until );  }

  bool is_marked()
  { return mark > -1; }

}; //Node_type

struct Is_smaller_node
{
  bool operator()(const Node_type &n1, const Node_type& n2 )
  {
    if( n1.serial_number < n2.serial_number )
      return true;

    return false;
  }

}; // Is_smaller_node


struct Is_smaller_edge
{
  bool operator()(const Node_type::Edge_type &e1, const Node_type::Edge_type& e2 )
  {
    if( e1.from < e2.from )
      return true;

    if( e2.from < e1.from )
      return false;

    if( e1.to < e2.to )
      return true;

    return false;
  }

}; // Is_smaller_edge


struct Is_heavier_edge
{
  bool operator()(const Node_type::Edge_type &e1, 
                  const Node_type::Edge_type & e2 )
  {
    if( e1.weight > e2.weight )
      return true;

    if( e1.weight < e2.weight )
      return false;

    // The rest of the code is for avoiding mixing
    // edges that are distinct but have the same weight.

    Is_smaller_edge ise;
    
    return ise(e1, e2);
  }

}; // Is_heavier_edge


struct Is_lighter_edge
{
  bool operator()(const Node_type::Edge_type &e1, 
                  const Node_type::Edge_type & e2 )
  {
    if( e1.weight < e2.weight )
      return true;

    if( e1.weight > e2.weight )
      return false;

    // The rest of the code is for avoiding mixing
    // edges that are distinct but have the same weight.

    Is_smaller_edge ise;
    
    return ise(e1, e2);
  }

}; // Is_heavier_edge


struct Is_heavier_cn
{
  bool operator()(const std::pair<Node_type::Edge_type, double> &e1, 
                  const std::pair<Node_type::Edge_type, double>& e2 )
  {
    if( e1.second > e2.second )
      return true;

    if( e1.second < e2.second )
      return false;

    // The rest of the code is for avoiding mixing
    // pairs that are distinct but have the same
    // double value.

    Is_smaller_edge ise;
    
    return ise(e1.first, e2.first);
  }

}; // Is_heavier_cn

 
class Delinquent_network
{
 public:

  typedef Node_type              Delinquent;
  typedef Delinquent::Edge_type  Connection;
  typedef std::vector<int>       Path;

 public:

  typedef std::vector<Connection>::iterator  Connection_iterator; 

 public:

  Delinquent_network():_number_of_connections(-1){}

  Delinquent_network( char * filename )
  {
    std::ifstream in(filename);

    // Reading first file with queries
    if( !( in.is_open() && in.good() ) )
    {
      std::cout << " There was a problem with opening the file that stores the network ... aborting " <<std::endl;
      std::exit(-1);
    }

    // Read the first set of lines, the ones that describe the delinquents

    std::string line;
    std::getline(in,line);

    int llline=0;

    while( in.good() && line[0]=='(' )
    {
      Delinquent dlq;

      int cfirst=1, c=1;

      // Get name

      while(c < line.size() && line[c] != ',' && line[c] != ' ' )
        c++;

      dlq.name = line.substr(cfirst,c-cfirst);

      while(c < line.size() && (line[c] == ',' || line[c] == ' ')  )
        c++;
    
      cfirst = c;

      // Get location of activity

      while(c < line.size() && line[c] != ',' && line[c] != ' ' )
        c++;

      dlq.place = line.substr(cfirst,c-cfirst);

      while(c < line.size() && (line[c] == ',' || line[c] == ' ')  )
        c++;
    
      cfirst = c;

      // Get period of recorded activity : From

      while(c < line.size() && line[c] != ',' && line[c] != ' ' && line[c] != '-' )
        c++;

      bool single_date = (line[c] == ',');

      dlq.active_since = boost::lexical_cast<int>(line.substr(cfirst,c-cfirst));

      while(c < line.size() && (line[c] == ',' || line[c] == ' ' || line[c] == '-') )
        c++;
    
      cfirst = c;

      if(!single_date)
      {
        // Get period of recorded activity : Until

        while(c < line.size() && line[c] != ',' && line[c] != ' ' )
          c++;

        dlq.active_until = boost::lexical_cast<int>(line.substr(cfirst,c-cfirst));

        while(c < line.size() && (line[c] == ',' || line[c] == ' ') )
          c++;
    
        cfirst = c;
      }
      else 
        dlq.active_until = dlq.active_since;

      // Get serial number

      while(c < line.size() && line[c] != ',' && line[c] != ' ' && line[c] != ')' )
        c++;

      dlq.serial_number = boost::lexical_cast<int>(line.substr(cfirst,c-cfirst));

      _nodes.push_back(dlq);

      line.clear();
      std::getline(in,line);
      
      llline++;

    } // while( in.good() && line[0]=='(' )

    std::sort(_nodes.begin(), _nodes.end(), Is_smaller_node());

    for(int jj=0; jj<_nodes.size(); jj++)
      _serials_to_nodes[_nodes[jj].serial_number] = jj;

    std::map< Connection, int, Is_smaller_edge >  _traded_items;
    bool keep_reading = true;

    do
    {
      assert(line[0] == '{');

      int cfirst=1, c=1, from=-1, to=-1;

      Connection cn;
      Path p;

      while( c < line.size() )
      {
        while( c < line.size() && line[c] != ',' && line[c] != ' ' && line[c] != '}' )
          c++;

        int serial = boost::lexical_cast<int>(line.substr(cfirst,c-cfirst));

        p.push_back(serial);

        if( from == -1 )
          from = _serials_to_nodes[serial];
        else
        {
          if( to == -1 )
            to = _serials_to_nodes[serial];
          else
          {
            from = to;
            to = _serials_to_nodes[serial];
          }

          cn.from = from;
          cn.to = to;

          if( _traded_items.find(cn) != _traded_items.end() )
            _traded_items[cn]++;
          else
            _traded_items[cn]=1;

        } // else of if( from == -1 ) 
   
        while( c < line.size() && ( line[c] == ',' || line[c] == ' ' || line[c] == '}') )
          c++;

        cfirst=c;

      } // while( c < line.size() )

      _paths.push_back(p);
      line.clear();
      std::getline(in,line);

      ++llline;

    } while( in.good() );

    // Flush all edges that were counted in the _traded_items map.

    _number_of_connections = 0;

  
    for( std::map< Connection, int, Is_smaller_edge >::iterator tr_it  = _traded_items.begin();
                                                                tr_it != _traded_items.end(); tr_it++ )
    {
      
      int from_index = (*tr_it).first.from,
          to_index = (*tr_it).first.to;
      
      Connection c; 
      c.from = from_index;
      c.to = to_index;
      c.weight = (*tr_it).second;

      _nodes[from_index].out_edges.push_back(c);
      _nodes[to_index].in_edges.push_back(c);

      _number_of_connections++;
    }

  } // Delinquent_network( char * filename )


  int number_of_delinquents()
  { return _nodes.size(); }

  int number_of_connections()
  {
    if( _number_of_connections != -1 )
      return _number_of_connections;

    _number_of_connections = 0;

    for(int i=0; i<_nodes.size(); i++ )
      _number_of_connections += _nodes[i].in_edges.size();

    return _number_of_connections;
  }

  Delinquent& delinquent(int i)
  { return _nodes[i]; }

  Delinquent& delinquent_from_serial(int sr)
  { return _nodes[_serials_to_nodes[sr]]; }

  Connection_iterator in_edges_begin( int i )
  { return _nodes[i].in_edges.begin(); }

  Connection_iterator in_edges_end( int i )
  { return _nodes[i].in_edges.end(); }

  Connection_iterator out_edges_begin( int i )
  { return _nodes[i].out_edges.begin(); }

  Connection_iterator out_edges_end( int i )
  { return _nodes[i].out_edges.end(); }

  int in_degree( int i )
  { return _nodes[i].in_edges.size(); }

  int out_degree( int i )
  { return _nodes[i].out_edges.size(); }

  int degree( int i )
  { return in_degree(i)+out_degree(i); }

  void insert_node( Delinquent &d )
  { _nodes.push_back(d); }

  void insert_path( Path &p )
  { _paths.push_back(p); }

  void insert_serial_to_node( int serial, int index)
  { _serials_to_nodes[serial] = index; }

  int serial_to_node_index( int serial)
  { return _serials_to_nodes[serial]; }

  bool has_edge( int sr1, int sr2 )
  {
    int ind1 = serial_to_node_index(sr1),
        ind2 = serial_to_node_index(sr2);

    for( int i=0; i< _nodes[ind1].out_edges.size(); i++ )
      if( _nodes[ind1].out_edges[i].to == ind2 )
        return true;  

    return false;
  }

  bool has_path( std::vector<int>& path )
  {
    if(path.size()==0)
      return false;
 
    if(path.size()==1)
      return (serial_to_node_index(path[0]) > 0);

    for( int i=0; i<path.size()-1; i++ )
      if( !has_edge(path[i],path[i+1]) )
        return false;  
 
    return true;
  }

  void print_path( std::vector<Delinquent> &path )
  {
    if(path.size() == 0)
    {
      std::cout << std::endl;
      return;
    }
    
    for( int i=0; i<path.size(); i++ )
    {
      std::cout << " " << path[i].name;

      if(i !=path.size()-1 )
        std::cout << " -->" ;
      else
        std::cout << std::endl;
    }
  }

  void print_path( std::vector<int> &path )
  {
    if(path.size() == 0)
    {
      std::cout << std::endl;
      return;
    }
    
    for( int i=0; i<path.size(); i++ )
    {
      std::cout << " " << _nodes[serial_to_node_index(path[i])].name;

      if(i !=path.size()-1 )
        std::cout << " -->" ;
      else
        std::cout << std::endl;
    }
  }

  // Returns the serial numbers of all the neighbours
  // of the node that has INDEX ind.
  template < class OutputIterator >
  void neighbours( int ind, OutputIterator ot )
  {
    std::set<int> nachbar;

    for( int i=0; i< _nodes[ind].in_edges.size(); i++ )
    {
      Delinquent from_node = _nodes[_nodes[ind].in_edges[i].from];
      nachbar.insert(from_node.serial_number);
    }

    for( int i=0; i< _nodes[ind].out_edges.size(); i++ )
    {
      Delinquent to_node = _nodes[_nodes[ind].out_edges[i].to];
      nachbar.insert(to_node.serial_number);
    }

    for( std::set<int>::iterator it = nachbar.begin(); it != nachbar.end(); it++ )
      *ot++ = *it;
  }


  // This differs from the degree() function
  // since it counts each distinct incident
  // node only once, and not once per edge.
  int number_of_neighbours( int i )
  {
    std::vector<int> nachbar;
    neighbours(i,std::back_inserter(nachbar));

    return nachbar.size(); 
  }


  // Compute the clustering coefficient of the node that has index ind.
  double clustering_coefficient( int ind )
  {
    std::vector<int> nachbar;
    neighbours(ind,std::back_inserter(nachbar));

    if(nachbar.size() == 0 || nachbar.size() == 1)
      return double(0.0);

    std::set<int> neighs;

    for(int j=0; j<nachbar.size(); j++)
      neighs.insert(nachbar[j]);    

    int total = 0;

    for(int j=0; j<nachbar.size(); j++)
    {
      std::vector<int> nachb;
      neighbours(nachbar[j],std::back_inserter(nachb));

      for( int k=0; k<nachb.size() ; k++ )
        if( neighs.find(nachb[k]) != neighs.end() && nachb[k] != ind )
          total++;    
    }

    return double(2.0)*double(total)/(double(nachbar.size())*double(nachbar.size()-1));
  }

  // Returns the average of the clustering coefficients of all nodes
  double average_clustering_coefficient()
  {  
    double avg(0.0);

    for( int i=0; i<_nodes.size(); i++ )
      avg += clustering_coefficient(i);

    return avg/double(_nodes.size());
  }

  bool is_scale_free()
  {
    int degree_cut_off = 25;
    std::vector<double> degrees;
    degrees.assign(_nodes.size(),double(0.0));

    for( int i=0; i<_nodes.size(); i++ )
      degrees[number_of_neighbours(i)] += double(1.0);

    for( int i=1; i< degree_cut_off; i++ )
      if( degrees[i] != 0 )
      {
        double p = degrees[i] /double(_nodes.size());

        // std::cout << " Probability of degree " << i <<" : " << p << std::endl; 
        // std::cout << "Upper bound: " << (double(1.0)/double(i*i)) << std::endl;
        // std::cout << "Lower bound: " << (double(1.0)/double(i*i*i)) << std::endl;

        if( p >= double(6.0)*(double(1.0)/double(i*i)) ||
            p < (double(1.0)/double(i*i*i))/double(6.0) )
          return false;
      }

    return true;
  }

  // Returns the serial numbers of all the neighbours
  // of the node that has SERIAL NUMBER sn.
  template < class OutputIterator >
  void neighbours_serials( int sn, OutputIterator ot )
  {
    int index = _serials_to_nodes[sn];

    return neighbours(index,ot);
  }


  // Returns the length (number of edges) of 
  // the  shortest directed path that starts 
  // from the node with index `index1` and 
  // ends at the node with index `index2`.

  int compute_distance( int index1, int index2 )
  {
    if( index1 < 0 || index2 < 0 || index1 >= _nodes.size() || index2 >= _nodes.size() )
      return -1;

    unmark_network();
    backward_BFS_labelling(index2);

    return _nodes[index1].mark;
  }


  // Erases all edges incident to the node that has index `index`
  void disconnect_node( int index )
  {
    for(int i=0; i<_nodes[index].in_edges.size(); i++)
    {
      int from_index = _nodes[index].in_edges[i].from;
     
      std::vector<Connection>::iterator it  = _nodes[from_index].out_edges.begin(); 

      while( it != _nodes[from_index].out_edges.end() && (*it).to != index )
        it++;
        
      assert(it!=_nodes[from_index].out_edges.end());

      _nodes[from_index].out_edges.erase(it);   
    }  

    for(int i=0; i<_nodes[index].out_edges.size(); i++)
    {
      int to_index = _nodes[index].out_edges[i].to;
     
      std::vector<Connection>::iterator it  = _nodes[to_index].in_edges.begin(); 

      while( it != _nodes[to_index].in_edges.end() && (*it).from != index  )
        it++;
        
      assert(it!=_nodes[to_index].in_edges.end());
      _nodes[to_index].in_edges.erase(it);   
    }    

    _nodes[index].in_edges.clear();
    _nodes[index].out_edges.clear();
  }

  // Returns the simple directed path P from node `index1` to node `index2`
  // for which each path edge e=(v1,v2) has the largest possible weight
  // among all the edges adjacent to v1 such that there exists a path P'
  // from v2 to node `index2`, and P' is simple and does not include
  // any vertices of the subpath P-P'. 

  template< class OutputIterator >
  void construct_greedy_capacity_path( int index1, int index2, OutputIterator ot )
  {
    Delinquent_network new_nw;

    // Create a copy of the network

    for( std::vector<Delinquent>::iterator rdit = _nodes.begin(); rdit != _nodes.end(); rdit++ )
      new_nw.insert_node( *rdit );

    for( std::vector<Path>::iterator rpit = _paths.begin(); rpit != _paths.end(); rpit++ )
      new_nw.insert_path( *rpit ); 

    for( std::map<int,int>::iterator it_stn  = _serials_to_nodes.begin(); 
                                     it_stn != _serials_to_nodes.end(); it_stn++ )
      new_nw.insert_serial_to_node( it_stn->first, it_stn->second );

    int curr_index = index1;
    std::vector<int> path;

    path.push_back(curr_index);

    while( curr_index != index2 )
    {
      std::vector<Connection> out_cn; 

      for( std::vector<Connection>::iterator it  = new_nw.out_edges_begin(curr_index);
                                             it != new_nw.out_edges_end(curr_index); it++ )
        out_cn.push_back(*it);

      new_nw.disconnect_node(curr_index);
      new_nw.unmark_network();
      new_nw.backward_BFS_labelling(index2);

      int max_weight=-1, next_index=-1;

      for( int i=0; i< out_cn.size() ; i++ )
        if( new_nw.delinquent(out_cn[i].to).is_marked() && out_cn[i].weight > max_weight )
        {
          next_index = out_cn[i].to;
          max_weight = out_cn[i].weight;
        }

      if( next_index == -1 )
        return;

      path.push_back(next_index);
      curr_index = next_index;
    }

    for( int i=0; i<path.size(); i++ )
      *ot++ = _nodes[path[i]];
  }


  // Same as above function, except now there is an aspect of
  // randomisation when selecting an edge that expands the path. 

  template< class OutputIterator >
  void construct_greedy_capacity_path_randomized
  ( int index1, int index2, OutputIterator ot, int seed = 1, double power = 1.0 )
  {
    CGAL::Random random(seed);

    Delinquent_network new_nw;

    // Create a copy of the network

    for( std::vector<Delinquent>::iterator rdit = _nodes.begin(); rdit != _nodes.end(); rdit++ )
      new_nw.insert_node( *rdit );

    for( std::vector<Path>::iterator rpit = _paths.begin(); rpit != _paths.end(); rpit++ )
      new_nw.insert_path( *rpit ); 

    for( std::map<int,int>::iterator it_stn  = _serials_to_nodes.begin(); 
                                     it_stn != _serials_to_nodes.end(); it_stn++ )
      new_nw.insert_serial_to_node( it_stn->first, it_stn->second );

    int curr_index = index1;
    std::vector<int> path;

    path.push_back(curr_index);

    while( curr_index != index2 )
    {
      std::vector<Connection> out_cn; 

      for( std::vector<Connection>::iterator it  = new_nw.out_edges_begin(curr_index);
                                             it != new_nw.out_edges_end(curr_index); it++ )
        out_cn.push_back(*it);

      new_nw.disconnect_node(curr_index);
      new_nw.unmark_network();
      new_nw.backward_BFS_labelling(index2);

      int next_index=-1;

      std::vector<Connection> marked_cn;
      double total_weight = 0.0, scaled_weight;

      for( int i=0; i< out_cn.size() ; i++ )
        if( new_nw.delinquent(out_cn[i].to).is_marked() )
        {
          scaled_weight = pow(out_cn[i].weight,power);
          marked_cn.push_back(out_cn[i]);
          marked_cn.back().weight = scaled_weight;
          total_weight += scaled_weight;         
        }

      if(marked_cn.empty())
        return;

      double picked_weight = random.get_double(0,total_weight),
             weight_sum=0.0;

      int j=0;

      while( picked_weight > weight_sum + marked_cn[j].weight )
      {
        weight_sum += marked_cn[j].weight;
        j++;  
      }

      next_index = marked_cn[j].to;
      path.push_back(next_index);
      curr_index = next_index;
    }

    for( int i=0; i<path.size(); i++ )
      *ot++ = _nodes[path[i]];
  }

  // Constructs a path on the graph between two nodes
  // with indices `index1` and `index2` using the 
  // maximum weight arboresence of the network
  // that is rooted at the node with index `index2`.
  // The function implements Prim's algorithm for 
  // constructing the arboresence.

  template< class OutputIterator >
  void construct_path_via_maximum_arboresence
  ( int index1, int index2, OutputIterator ot )
  {
    if( index1 == index2 )
    {
      *ot++ = _nodes[index2];
      return;
    }

    std::priority_queue<Connection, std::vector<Connection>, Is_lighter_edge> wavefront_edges;
    std::set<Connection, Is_smaller_edge> selected_edges;

    unmark_network();
    _nodes[index2].mark = 1;

    for(int i=0; i< _nodes[index2].in_edges.size(); i++ )
    {
      int neighbour = _nodes[index2].in_edges[i].from;
      
      if( _nodes[neighbour].is_marked() == false )
        wavefront_edges.push(_nodes[index2].in_edges[i]);
    }


    // Execute Pim's algorithm and mark the edges of the arboresence on the current network.

    int label = 2;

    while( !wavefront_edges.empty() )
    {
      while( !wavefront_edges.empty() && 
             _nodes[wavefront_edges.top().from].is_marked() )
        wavefront_edges.pop();



      if( !wavefront_edges.empty() )
      {
        int curr_index = wavefront_edges.top().from;

        selected_edges.insert(wavefront_edges.top());

        wavefront_edges.pop();
        _nodes[curr_index].mark = label++;
     
        for(int i=0; i< _nodes[curr_index].in_edges.size(); i++ )
        {
          int neighbour = _nodes[curr_index].in_edges[i].from;

          if( _nodes[neighbour].is_marked() == false )
            wavefront_edges.push(_nodes[curr_index].in_edges[i]);
         
        } // for(int i=0; ... )
        
      } // if( !wavefront_edges.empty() )

    } // while( !wavefront_edges.empty() )

    if( _nodes[index1].is_marked() == false )
      return;

    int t_index = index1;

    *ot++ = _nodes[t_index];

    do
    {
      int max_weight=-1;

      for( int i=0; i<_nodes[t_index].out_edges.size(); i++ )
      {
        if( selected_edges.find(_nodes[t_index].out_edges[i]) != selected_edges.end() )
        {
          t_index = _nodes[t_index].out_edges[i].to;
          break;
        }
      }

      *ot++ = _nodes[t_index];

    }while(t_index != index2);

  } // construct_path_via_maximum_arboresence(...)


  // Construct the maximum weight path of legth `d` 
  // between nodes with indices `index1` and `index2`

  template< class OutputIterator >
  void construct_maximum_weight_path_of_length
  ( int index1, int index2, int d, OutputIterator ot )
  {
    unmark_network();

    // Make an index number for each edge,
    // to use it for indicating the corresponding
    // variable in the IP program.  

    std::map<Connection,int,Is_smaller_edge>  edges_to_vars;
    std::map<int,Connection> vars_to_edges;

    int variable_index = 0;

    for( int i=0; i<_nodes.size(); i++ )
      for( int j=0; j<_nodes[i].in_edges.size(); j++ )
      {
        edges_to_vars[_nodes[i].in_edges[j]] = variable_index;
        vars_to_edges[variable_index] = _nodes[i].in_edges[j];
        variable_index++;
      }

    CGAL::Quadratic_program<int> ip(CGAL::EQUAL, true, 0, false, 0);
    CGAL::Quadratic_program_solution<double> solution;    

    int equation_index = 0;

    // Restriction #1: for every node, except the ones with indices 
    // `index1` and `index2`, the number of selected in-edges equals 
    // the number of the selected out-edges.

    for( int i=0; i<_nodes.size(); i++ )
      if( i != index1 && i != index2 )
      {  
        for( int j=0; j<_nodes[i].in_edges.size(); j++ )
          ip.set_a(edges_to_vars[_nodes[i].in_edges[j]],equation_index,1);

        for( int j=0; j<_nodes[i].out_edges.size(); j++ )
          ip.set_a(edges_to_vars[_nodes[i].out_edges[j]],equation_index,-1);

        ip.set_b(equation_index, 0);
 	ip.set_r(equation_index, CGAL::EQUAL); 

        equation_index++;
      }    


    // Restriction #2: Every node, except the ones with indices 
    // `index1` and `index2`, has at most one selected in-edge,
    // and at most one selected out-edge.

    for( int i=0; i<_nodes.size(); i++ )
      if( i != index1 && i != index2 )
      {  
        for( int j=0; j<_nodes[i].in_edges.size(); j++ )
          ip.set_a(edges_to_vars[_nodes[i].in_edges[j]],equation_index,1);

        ip.set_b(equation_index,1);
 	ip.set_r(equation_index, CGAL::SMALLER); 

        equation_index++;

        for( int j=0; j<_nodes[i].out_edges.size(); j++ )
          ip.set_a(edges_to_vars[_nodes[i].out_edges[j]],equation_index,1);

        ip.set_b(equation_index,1);
 	ip.set_r(equation_index, CGAL::SMALLER);

        equation_index++;
      } 


    // Restriction #3: Node with `index1` has exactly one selected out-edge, 
    // and node with `index2` has exactly one selected in-edge.
      
    for( int j=0; j<_nodes[index1].out_edges.size(); j++ )
      ip.set_a(edges_to_vars[_nodes[index1].out_edges[j]],equation_index,1);

    ip.set_b(equation_index,1);
    ip.set_r(equation_index, CGAL::EQUAL); 

    equation_index++;

    for( int j=0; j<_nodes[index2].in_edges.size(); j++ )
      ip.set_a(edges_to_vars[_nodes[index2].in_edges[j]],equation_index,1);

    ip.set_b(equation_index,1);
    ip.set_r(equation_index, CGAL::EQUAL);

    equation_index++;


    // Restriction #4 The number of path edges should be equal to d.

    if( d >= 0 )
    {
      for( int i=0; i<_nodes.size(); i++ )
        for( int j=0; j<_nodes[i].in_edges.size(); j++ )
          ip.set_a(edges_to_vars[_nodes[i].in_edges[j]],equation_index,1);

      ip.set_b(equation_index,d);
      ip.set_r(equation_index, CGAL::EQUAL); 
    }

    // Value restriction: Every variable should have value at most one.

    for( int i=0; i<_nodes.size(); i++ )
      for( int j=0; j<_nodes[i].in_edges.size(); j++ )    
        ip.set_u(edges_to_vars[_nodes[i].in_edges[j]], true, 1);    
   

    // Definition of objective function.

    for( int i=0; i<_nodes.size(); i++ )
      for( int j=0; j<_nodes[i].in_edges.size(); j++ )
        ip.set_c(edges_to_vars[_nodes[i].in_edges[j]], -_nodes[i].in_edges[j].weight);


    solution = CGAL::solve_linear_program(ip, double());

    if(solution.is_infeasible())
      return;

    int v_index = 0;


    for( CGAL::template Quadratic_program_solution<double>::Variable_value_iterator 
         v_it = solution.variable_values_begin(); v_it != solution.variable_values_end(); v_it++ )
    {
      if( *v_it != CGAL::Quotient<double>(0.0) )
        _nodes[vars_to_edges[v_index].to].mark = 1;  

      v_index++;
    }



    std::set<int> node_set;
    int index_p = index1;

    node_set.insert(index1);

    while(index_p != index2) 
    {


      *ot++ = _nodes[index_p];

      int temp_p;
      
      for( int i=0; i<_nodes[index_p].out_edges.size(); i++ )
      {
        if( _nodes[_nodes[index_p].out_edges[i].to].is_marked() )
        {

          if( node_set.find(_nodes[index_p].out_edges[i].to) == node_set.end())
          {
            temp_p = _nodes[index_p].out_edges[i].to;
            node_set.insert(temp_p);
          }
        }
      }

      index_p = temp_p;

    }

    *ot++ = _nodes[index_p];

  

  } // void construct_maximum_weight_path( ... )


  template< class OutputIterator >
  void construct_maximum_weight_path
  ( int index1, int index2, OutputIterator ot )
  { construct_maximum_weight_path_of_length(index1,index2,-1,ot); }

  template< class OutputIterator >
  bool construct_shortest_path( int index1, int index2, OutputIterator ot )
  {
    unmark_network();
    backward_BFS_labelling(index2);

    bool is_unique = true;

    int index_t = index1;

    if( !_nodes[index_t].is_marked() )
      return false;

    *ot++ = _nodes[index_t];

    if(index_t == index2 )
      return true;

    do
    {
      int fathers = 0, max_weight=-1, max_index=index_t;

      for( int i=0; i<_nodes[index_t].out_edges.size(); i++ )      
        if( _nodes[_nodes[index_t].out_edges[i].to].mark == (_nodes[index_t].mark-1) )
        {
          fathers++;

          if( _nodes[index_t].out_edges[i].weight > max_weight )
          {
            max_index = _nodes[index_t].out_edges[i].to;
            max_weight = _nodes[index_t].out_edges[i].weight;
          }
        }
     
      index_t = max_index;

      *ot++ = _nodes[index_t];

      if( fathers > 1 )
        is_unique = false;

    }while( index_t != index2 );

    return is_unique;
  }

  void construct_possible_path_with_different_methods( int sr1, int sr2 )
  {
    int index1 = _serials_to_nodes[sr1],
        index2 = _serials_to_nodes[sr2];  


    std::vector<Delinquent>  path;

    construct_greedy_capacity_path(index1, index2, std::back_inserter(path));

    std::cout << std::endl;

    std::cout << " ********************************************************** " << std::endl;
    std::cout << " The greedy deterministic method yields the following path : " << std::endl;
    
    for( int i=0; i<path.size(); i++ )
    {
      std::cout << " " << path[i].name;

      if(i !=path.size()-1 )
        std::cout << " -->" ;
      else
      {
        std::cout << std::endl;
    std::cout << " ********************************************************** " << std::endl;
      }
    }

    std::cout << std::endl << std::endl;

    std::cout << " ********************************************************** " << std::endl;
    std::cout << " The greedy randomized method yields the following paths : " << std::endl;

    for( int seed = 0; seed < 5; seed++ )
    {
      path.clear();

      construct_greedy_capacity_path_randomized(index1, index2, std::back_inserter(path),seed);

      for( int i=0; i<path.size(); i++ )
      {
        std::cout << " " << path[i].name;

        if(i !=path.size()-1 )
          std::cout << " -->" ;
        else
          std::cout << std::endl;
      }
    }

    std::cout << " ********************************************************** " << std::endl;

    path.clear();

    construct_path_via_maximum_arboresence(index1, index2, std::back_inserter(path));

    std::cout << std::endl << std::endl;

    std::cout << " ********************************************************** " << std::endl;
    std::cout << " The max-arboresence method yields the following path : " << std::endl;
    
    for( int i=0; i<path.size(); i++ )
    {
      std::cout << " " << path[i].name;

      if(i !=path.size()-1 )
        std::cout << " -->" ;
      else
      {
        std::cout << std::endl;
    std::cout << " ********************************************************** " << std::endl;
      }
    }

    path.clear();

    bool is_unique = construct_shortest_path(index1, index2, std::back_inserter(path));

    std::cout << std::endl << std::endl;

    std::cout << " ********************************************************** " << std::endl;
    std::cout << " The shortest-path method yields the following path : " << std::endl;
    
    for( int i=0; i<path.size(); i++ )
    {
      std::cout << " " << path[i].name;

      if(i !=path.size()-1 )
        std::cout << " -->" ;
      else
      {
        std::cout << std::endl << std::endl;
   
        if(is_unique)
          std::cout << " There is a unique shortest path. " << std::endl;
        else
          std::cout << " There shortest path is NOT unique. " << std::endl;

    std::cout << " ********************************************************** " << std::endl;
      }
    }

    path.clear();

    Delinquent_network dlqn = extract_network_between_nodes(index1, index2);

    int ind1 = dlqn.serial_to_node_index(sr1),
        ind2 = dlqn.serial_to_node_index(sr2);

    std::cout << " Number of nodes in subnetwork: " << dlqn.number_of_delinquents() << std::endl;
    std::cout << " Number of connections in subnetwork: " << dlqn.number_of_connections() << std::endl;

   // dlqn.construct_maximum_weight_path(ind1, ind2, std::back_inserter(path));

   // std::cout << std::endl << std::endl;

   // std::cout << " ***************************** " << std::endl << std::endl;
   // std::cout << " The max-weight path method yields the following path : " << std::endl;
    
   // for( int i=0; i<path.size(); i++ )
   // {
   //   std::cout << path[i].name;

   //   if(i !=path.size()-1 )
   //     std::cout << " --> ";
   //   else
   //   {
   //     std::cout << std::endl;
   //     std::cout << " ***************************** " << std::endl;
   //   }
   // }

  } // void construct_possible_path_with_different_methods(...)


  Delinquent_network  extract_network_at_period( int moment_since, int moment_until )
  {
    std::vector<Delinquent> f_nodes;
    std::vector<Path>       f_paths;
    std::map<int,int>       stn;
    std::map< Connection, int, Is_smaller_edge >  f_traded_items;

    Delinquent_network new_network;

    // Extract only those delinquents that 
    // were active during the given period.
  
    for( int i=0; i<_nodes.size(); i++ )
      if( _nodes[i].was_active(moment_since, moment_until) )
      {
        Delinquent dq;

        dq.name = _nodes[i].name;
        dq.place = _nodes[i].place;
        dq.longitude = _nodes[i].longitude;
        dq.latitude = _nodes[i].latitude;
        dq.active_since = _nodes[i].active_since;
        dq.active_until = _nodes[i].active_until;
        dq.serial_number = _nodes[i].serial_number;

        f_nodes.push_back(dq);
      }

    std::map<int,int> new_node_indices;

    for( int i=0; i<f_nodes.size(); i++ )
      stn[f_nodes[i].serial_number]=i;

    // Extract those paths that involve only active delinquents

    for( int i=0; i< _paths.size(); i++ )
    {
      bool keep_path = true;

      for( int j=0; j<_paths[i].size(); j++ )
        if( stn.find(_paths[i][j]) == stn.end() )
          keep_path = false;

      if( keep_path == true )
        f_paths.push_back(_paths[i]);

    } // for( int i=0; i< _paths.size(); i++ )

    Connection cn;

    // Create the edge set that is infered from the extracted paths 

    for( int i=0; i<f_paths.size(); i++ )
      for( int j=1; j<f_paths[i].size(); j++ )
      {
        cn.from = stn[f_paths[i][j-1]];
        cn.to = stn[f_paths[i][j]];

        if( f_traded_items.find(cn) != f_traded_items.end() )
          f_traded_items[cn]++;
        else
          f_traded_items[cn]=1;
      }

    for( std::map< Connection, int, Is_smaller_edge >::iterator tr_it  = f_traded_items.begin();
                                                                tr_it != f_traded_items.end(); tr_it++ )
    { 
      cn.from = (*tr_it).first.from;
      cn.to = (*tr_it).first.to;
      cn.weight = (*tr_it).second;

      f_nodes[cn.from].out_edges.push_back(cn);
      f_nodes[cn.to].in_edges.push_back(cn);
    }

    for( std::vector<Delinquent>::iterator rdit = f_nodes.begin(); rdit != f_nodes.end(); rdit++ )
      new_network.insert_node( *rdit );

    for( std::vector<Path>::iterator rpit = f_paths.begin(); rpit != f_paths.end(); rpit++ )
      new_network.insert_path( *rpit ); 

    for( std::map<int,int>::iterator it_stn = stn.begin(); it_stn != stn.end(); it_stn++ )
      new_network.insert_serial_to_node( it_stn->first, it_stn->second );

    return new_network;

  } // extract_network_at_period( int moment_since, int moment_until )


  // The following function constructs the induced subgraph that
  // contains all those nodes that fall on a path between node 
  // with index `index1` and node with index `index2`.
  // BE CAREFULL: 1) The output of this function is not exactly 
  //                  the claimed subgraph. It is is just the subgraph
  //                 induced by all nodes V' such that for each v \in V' 
  //                 there exists a simple path from node that corresponds
  //                 to index1 to v, and there exists a simple path from
  //                 v to the node that corresponds to index2. This subgraph
  //                 is not always what we are looking for. However the 
  //                 returned subgraph maybe manually changed to what we want,
  //                 as it is always a superset of the solution that we want 
  //                 to compute.                  
  //              2) the returned network does not store any paths.

  Delinquent_network  extract_network_between_nodes( int index1, int index2 )
  {
    std::vector<Delinquent> f_nodes;
    std::map<int,int>       stn;
    int sr1 = _nodes[index1].serial_number,
        sr2 = _nodes[index2].serial_number;      

    Delinquent_network new_network;

    // Extract only those delinquents that 
    // can be reached from node[index1] and can
    // reach node[index2].

    std::set<int> shortlisted_nodes;
  
    unmark_network();
    forward_BFS_labelling(index1);

    for( int i=0; i<_nodes.size(); i++ )
      if(_nodes[i].is_marked())
        shortlisted_nodes.insert(_nodes[i].serial_number);
    
    unmark_network();
    backward_BFS_labelling(index2);

    for( int i=0; i<_nodes.size(); i++ )
      if( _nodes[i].is_marked() && 
          shortlisted_nodes.find(_nodes[i].serial_number) != shortlisted_nodes.end() )
        f_nodes.push_back(_nodes[i]);

    for( int i=0; i<f_nodes.size(); i++ )
      stn[f_nodes[i].serial_number]=i;

    for( int i=0; i<f_nodes.size(); i++ )
    {
      std::vector<Connection> temp_edges;

      for( int j=0; j<f_nodes[i].out_edges.size(); j++ )
      {
        int sr = _nodes[f_nodes[i].out_edges[j].to].serial_number;

        if( stn.find(sr) != stn.end() )
        {       
          Connection cn;
          cn.from = i;
          cn.to = stn[sr];
          cn.weight = f_nodes[i].out_edges[j].weight;

          temp_edges.push_back(cn);
        }

      } // for( int j=0; j<f_nodes[i].out_edges.size(); j++ )

      f_nodes[i].out_edges.clear();
        
      for( int k=0 ; k<temp_edges.size(); k++ )
        f_nodes[i].out_edges.push_back(temp_edges[k]);

      temp_edges.clear();

      for( int j=0; j<f_nodes[i].in_edges.size(); j++ )
      {
        int sr = _nodes[f_nodes[i].in_edges[j].from].serial_number;

        if( stn.find(sr) != stn.end() )
        {       
          Connection cn;
          cn.from = stn[sr];
          cn.to = i;
          cn.weight = f_nodes[i].in_edges[j].weight;

          temp_edges.push_back(cn);
        }

      } // for( int j=0; j<f_nodes[i].in_edges.size(); j++ )     

      f_nodes[i].in_edges.clear();
        
      for( int k=0 ; k<temp_edges.size(); k++ )
        f_nodes[i].in_edges.push_back(temp_edges[k]);

    } // for( int i=0; i<f_nodes.size(); i++ )


    for( std::vector<Delinquent>::iterator rdit = f_nodes.begin(); rdit != f_nodes.end(); rdit++ )
      new_network.insert_node( *rdit );

    for( std::map<int,int>::iterator it_stn = stn.begin(); it_stn != stn.end(); it_stn++ )
      new_network.insert_serial_to_node( it_stn->first, it_stn->second );

    return new_network;
 
  } // extract_network_at_period( int moment_since, int moment_until )


  Delinquent_network  extract_network_at_moment( int moment )
  { return extract_network_at_period(moment,moment); }

  template < class OutputIterator >
  void predict_missing_links_Jaccard( int num, OutputIterator ot, int bound = 5 ) 
  {
    std::vector< std::pair<Connection, double> > missing_links;

    for( int i=0; i<_nodes.size(); i++ )
    {
      std::vector<int> ni;
      std::set<int> sni;
      this->neighbours(i, std::back_inserter(ni));

      for( int k=0; k<ni.size(); k++ )
        sni.insert(ni[k]);

      for( int j=0; j<i; j++ )
      {
        std::vector<int> nj;
        std::set<int> snj; 
 
        this->neighbours(j, std::back_inserter(nj));


        for( int k=0; k<nj.size(); k++ )
          snj.insert(nj[k]);

        bool coexisted = ( _nodes[i].active_since > 0 && _nodes[i].active_until > 0 &&
                           _nodes[j].active_since > 0 && _nodes[j].active_until > 0 &&
                           _nodes[i].was_active(_nodes[j].active_since, _nodes[j].active_until));


        if( _nodes[i].name == std::string("White_Levy") && _nodes[j].name == std::string("Hunt_Brothers") )
        {
          std::cout << " Vrhka White-Hunt" << std::endl;
          std::cout << " Sni passes bound: " << (sni.size() >= bound) << std::endl;
          std::cout << " Snj passes bound: " << (snj.size() >= bound) << std::endl;
          std::cout << " Snj size: " << snj.size() << std::endl;
          std::cout << " Found .end(): " << (sni.find(_nodes[j].serial_number) == sni.end()) << std::endl;
        }
//        std::cout << " Coexisted: " << coexisted << std::endl;

        if( sni.find(_nodes[j].serial_number) == sni.end() 
            && sni.size() >= bound && snj.size() >=bound /*&& coexisted*/ )
        {
          std::vector<int> intrsct, unionn;
          Connection cn;

          //std::cout << " Perasa! " << std::endl;

          std::set_intersection(sni.begin(), sni.end(), snj.begin(), snj.end(), std::back_inserter(intrsct) );
          std::set_union(sni.begin(), sni.end(), snj.begin(), snj.end(), std::back_inserter(unionn) );
            
          cn.from = i;
          cn.to = j;

          if( intrsct.size() !=0 )
            missing_links.push_back( std::make_pair(cn,double(double(intrsct.size())/double(unionn.size())) ) );
        } 
        //else
          //std::cout << " Den perasa " << std::endl;

      } // for( int j=0; j<i; j++ )
     
    } // for( int i=0; i<_nodes.size(); i++ )

    std::sort(missing_links.begin(), missing_links.end(), Is_heavier_cn() );

    for( int i=0; i< std::min(num,int(missing_links.size())); i++ )
      *ot++ = missing_links[i];
  }

  template < class OutputIterator >
  void predict_missing_links_clique( int num, OutputIterator ot ) 
  {
    std::vector< std::pair<Connection, double> > missing_links;

    for( int i=0; i<_nodes.size(); i++ )
    {
      std::vector<int> ni;
      std::set<int> sni;
      this->neighbours(i, std::back_inserter(ni));

      for( int k=0; k<ni.size(); k++ )
        sni.insert(ni[k]);

      for( int j=0; j<i; j++ )
      {
        std::vector<int> nj;
        std::set<int> snj; 
 
        this->neighbours(j, std::back_inserter(nj));


        for( int k=0; k<nj.size(); k++ )
          snj.insert(nj[k]);

        bool coexisted = ( _nodes[i].active_since > 0 && _nodes[i].active_until > 0 &&
                           _nodes[j].active_since > 0 && _nodes[j].active_until > 0 &&
                           _nodes[i].was_active(_nodes[j].active_since, _nodes[j].active_until));


        if( sni.find(_nodes[j].serial_number) == sni.end() /*&& coexisted*/ )
        {
          std::vector<int> intrsct;
          Connection cn;

          std::set_intersection(sni.begin(), sni.end(), snj.begin(), snj.end(), std::back_inserter(intrsct) );
            
          cn.from = i;
          cn.to = j;

          missing_links.push_back( std::make_pair( cn,double(std::min(sni.size(), snj.size())) ) );
        } 

      } // for( int j=0; j<i; j++ )
     
    } // for( int i=0; i<_nodes.size(); i++ )

    std::sort(missing_links.begin(), missing_links.end(), Is_heavier_cn() );

    for( int i=0; i< std::min(num,int(missing_links.size())); i++ )
      *ot++ = missing_links[i];
  }

  void export_as_txt()
  {
    std::cout << std::endl << std::endl;

    std::cout << " Number of delinquents in the network: " << this->number_of_delinquents() << std::endl;
    std::cout << " Number of connections in the network: " << this->number_of_connections() << std::endl;

    std::cout << " The average clustering coefficient of the network is: " 
              << this->average_clustering_coefficient() << std::endl << std::endl;


    std::cout<< " List with delinquents and their number of neighbours: " << std::endl;
    std::cout<< " ***************************************************** " << std::endl;
 
    for( int i=0; i < _nodes.size(); i++ )
      std::cout << _nodes[i].name << " : " <<  this->degree(i) << std::endl; 


    std::cout << std::endl;


    std::cout<< " Delinquents: " << std::endl;
    std::cout<< " ************ " << std::endl;

    for( int i=0; i<_nodes.size(); i++ )
      std::cout << _nodes[i].name << ", lives at " <<  _nodes[i].place << " and is known to be active since " 
                << _nodes[i].active_since << " until " << _nodes[i].active_until << std::endl;

    std::cout << std::endl << std::endl << std::endl;
    
    std::cout<< " Connections: " << std::endl;
    std::cout<< " ************ " << std::endl;

    for( int i=0; i<_nodes.size(); i++ )
    {
      std::cout << _nodes[i].serial_number << ") Delinquent: " << _nodes[i].name << std::endl << std::endl; 

      std::cout << "   Got items from: " << std::endl;
      std::cout << "   --------------- " << std::endl;

      for( int j=0; j < _nodes[i].in_edges.size(); j++ )
        std::cout << _nodes[_nodes[i].in_edges[j].from].name 
                  << " as many as " << _nodes[i].in_edges[j].weight << std::endl;


      std::cout << std::endl;

      std::cout << "   Gave items to: " << std::endl;
      std::cout << "   -------------- " << std::endl;

      for( int j=0; j < _nodes[i].out_edges.size(); j++ )
        std::cout << _nodes[_nodes[i].out_edges[j].to].name 
                  << " as many as " << _nodes[i].out_edges[j].weight << std::endl;

      std::cout << std::endl << std::endl;

    }

    std::cout << std::endl << std::endl << std::endl;

    std::cout<< " Recorded Paths: " << std::endl;
    std::cout<< " *************** " << std::endl;

    for( int i=0; i<_paths.size(); i++ )
    {
      std::cout << " Path #" << (i+1) << " : " << std::endl; 
      std::cout << " ------------ " << std::endl;

      for( int j=0; j < _paths[i].size(); j++ )
      {
        std::cout << _nodes[_serials_to_nodes[_paths[i][j]]].name;

        if( j < _paths[i].size()-1 )
          std::cout << " -> ";
        else
          std::cout << std::endl << std::endl;
      } 

    } // for( int i=0; i<_paths.size(); i++ )

  } // void export_as_txt()


  void export_as_Mathematica_code( char *filename, bool labeled = true, 
                                   bool tag_with_names = false, bool arrows = true )
  {
    std::ofstream out(filename);

    bool printed_edges = false;

    out << " Graph[ " << std::endl << std::endl << std::endl ;
    out << " { " << std::endl;

    for( int i=0; i<_nodes.size(); i++ )
      for( int j=0; j<_nodes[i].in_edges.size(); j++ )
      {
        if(printed_edges)
          out << " ," << std::endl;

        if( j==0 )
          out << std::endl;

        printed_edges = true;


        if( labeled )
          out << " Labeled[ "; 

        if( tag_with_names )
          out << "Style[" << "\"" << _nodes[_nodes[i].in_edges[j].from].name << "\"" 
                          << ", FontSize -> 13, FontColor -> Black ]";
        else
          out << "Style[" << (_nodes[_nodes[i].in_edges[j].from].serial_number) 
                          << ", FontSize -> 13, FontColor -> Black]"; 
        if(arrows)
          out << " -> " ;
        else 
          out << " <-> " ;

        if( tag_with_names )
          out << "Style[" << "\"" << _nodes[_nodes[i].in_edges[j].to].name << "\"" 
                          << ", FontSize -> 13, FontColor -> Black ]";
        else
          out << "Style[" << (_nodes[_nodes[i].in_edges[j].to].serial_number) 
                          << ", FontSize -> 13, FontColor -> Black ]";

        if( labeled )
          out << " , " << "Style[" << _nodes[i].in_edges[j].weight 
                       << ", FontSize -> 13, FontColor-> Black ] ]"; 

      } // for( int j=0; j<_nodes[i].in_edges.size(); j++ )

      out << std::endl << " }," << std::endl;

      out << std::endl << std::endl;
      out << " VertexLabels -> Placed[\"Name\", Above], " << std::endl;
      out << " VertexSize -> 0.2, " << std::endl;
      out << " VertexStyle -> White, " << std::endl;
      out << " EdgeStyle -> RGBColor[{0.2,0.2,1.0}], " << std::endl;
      out << " EdgeShapeFunction -> GraphElementData[{\"FilledArrow\", \"ArrowSize\" -> .012}], " << std::endl;
      out << " ImagePadding -> 50, " << std::endl;
      out << " ImageSize -> 1100 " << std::endl;
      out << "]" ;
    

  } // export_as_Mathematica_code(...)


  void export_as_Mathematica_GraphPlot( char *filename, bool labeled = true, 
                                   bool tag_with_names = false, bool arrows = true )
  {
    std::ofstream out(filename);

    bool printed_edges = false;

    out << " GraphPlot[ " << std::endl << std::endl << std::endl ;
    out << " { " << std::endl;

    for( int i=0; i<_nodes.size(); i++ )
      for( int j=0; j<_nodes[i].in_edges.size(); j++ )
      {
        if(printed_edges)
          out << " ," << std::endl;

        if( j==0 )
          out << std::endl;

        printed_edges = true;


    
        out << " { "; 

        if( tag_with_names )
          out << "Style[" << "\"" << _nodes[_nodes[i].in_edges[j].from].name << "\"" 
                          << ", FontSize -> 10, FontColor -> Black ]";
        else
          out << "Style[" << (_nodes[_nodes[i].in_edges[j].from].serial_number) 
                          << ", FontSize -> 10, FontColor -> Black]"; 
        if(arrows)
          out << " -> " ;
        else 
          out << " <-> " ;

        if( tag_with_names )
          out << "Style[" << "\"" << _nodes[_nodes[i].in_edges[j].to].name << "\"" 
                          << ", FontSize -> 10, FontColor -> Black ]";
        else
          out << "Style[" << (_nodes[_nodes[i].in_edges[j].to].serial_number) 
                          << ", FontSize -> 10, FontColor -> Black ]";

        if( labeled )
          out << " , " << "Style[" << _nodes[i].in_edges[j].weight 
                       << ", FontSize -> 13, FontColor-> Black ]";

        out << " }";
 

      } // for( int j=0; j<_nodes[i].in_edges.size(); j++ )

      out << std::endl << " }," << std::endl;

      out << std::endl << std::endl;
      out << " VertexLabels -> Placed[\"Name\", Above], " << std::endl;
      out << " VertexSize -> 0.2, " << std::endl;
      out << " VertexStyle -> White, " << std::endl;
      out << " EdgeStyle -> RGBColor[{0.2,0.2,1.0}], " << std::endl;
      out << " EdgeShapeFunction -> GraphElementData[{\"FilledArrow\", \"ArrowSize\" -> .012}], " << std::endl;
      out << " ImagePadding -> 50, " << std::endl;
      out << " ImageSize -> 1100 " << std::endl;
      out << "]" ;
    

  } // export_as_Mathematica_GraphPlot( char *filename, ... )


  void export_as_Mathematica_code_undirected( char *filename )
  {
    std::ofstream out(filename);

    std::set<Connection, Is_smaller_edge> edge_set;

    for( int i=0; i<_nodes.size(); i++ )
      for( int j=0; j<_nodes[i].in_edges.size(); j++ )
      {
        Connection inv;
        inv.from = _nodes[i].in_edges[j].to; 
        inv.to = _nodes[i].in_edges[j].from;

        if( edge_set.find(inv) == edge_set.end() )
          edge_set.insert(_nodes[i].in_edges[j]);
      }


    out << " Graph[ " << std::endl << std::endl << std::endl ;
    out << " { " << std::endl;

    int j=0;

    for( std::set<Connection,Is_smaller_edge>::iterator it = edge_set.begin(); it != edge_set.end(); it++  )
    {
      out << "UndirectedEdge[" << "Style[\"" << (_nodes[(*it).from].name) << "\",FontSize->13]";
      out << " , " ;
      out << "Style[\"" << (_nodes[(*it).to].name) << "\",FontSize->13]] ";

      if( j< edge_set.size()-1 )
        out << " ," << std::endl;
      else 
        out << std::endl;

      j++;
    } 

    out << " }," << std::endl;

    out << std::endl << std::endl;
    out << " VertexLabels -> Placed[\"Name\", Above], " << std::endl;
    out << " VertexSize -> Large, " << std::endl;
    out << " VertexStyle -> White, " << std::endl;
    out << " EdgeStyle -> {Blue, Thick}, " << std::endl;
    out << " ImageSize -> 1100, " << std::endl;
    out << " ImagePadding -> 50 " << std::endl;
    out << "]" ;
    

  } // export_as_Mathematica_code_undirected( char *filename )

 private:

  void unmark_network()
  {
    for( int i=0; i<_nodes.size(); i++ )
      _nodes[i].mark = -1;
  }

  // Starting from the node with index ind, 
  // execute a BFS by traversing only the out-edges
  // of each visited node. All visited nodes get marked
  // with an integer that equals their distance to 
  // the source node. 
  // Precondition: None of the network nodes is marked. 

  void forward_BFS_labelling( int ind )
  {
    std::queue< std::pair<int,int> > visited; 
    visited.push( std::make_pair(ind,0) );
    
    while(!visited.empty())
    {
      std::pair<int,int> pr = visited.front();
      int front_index = pr.first;
      int dist = pr.second;

      visited.pop();

      if( _nodes[front_index].is_marked() == false )
      {
        _nodes[front_index].mark = dist;
        
        for( int i=0; i<_nodes[front_index].out_edges.size(); i++ )
        {
          int to_index = _nodes[front_index].out_edges[i].to;

          if( _nodes[to_index].is_marked() == false )
            visited.push( std::make_pair(to_index, dist+1) );

        } // for( int i=0; i<_nodes[front_index].out_edges.size(); i++ )

      } // if( _node[front_index].mark == false )

    } // while(!visited.empty())

  } // void forward_BFS_labelling( int ind )


  // Starting from the node with index ind, 
  // execute a BFS by traversing only the in-edges
  // of each visited node. All visited nodes get marked
  // with an integer that equals their distance to 
  // the source node. 
  // Precondition: None of the network nodes is marked. 

  void backward_BFS_labelling( int ind )
  {
    std::queue< std::pair<int,int> > visited; 
    visited.push( std::make_pair(ind,0) );
    
    while(!visited.empty())
    {
      std::pair<int,int> pr = visited.front();
      int front_index = pr.first;
      int dist = pr.second;

      visited.pop();

      if( _nodes[front_index].is_marked() == false )
      {
        _nodes[front_index].mark = dist;
        
        for( int i=0; i<_nodes[front_index].in_edges.size(); i++ )
        {
          int from_index = _nodes[front_index].in_edges[i].from;

          if( _nodes[from_index].is_marked() == false )
            visited.push( std::make_pair(from_index, dist+1) );

        } // for( int i=0; i<_nodes[front_index].in_edges.size(); i++ )

      } // if( _node[front_index].mark == false )

    } // while(!visited.empty())

  } // void backward_BFS_labelling( int ind )

 private:

  std::vector<Delinquent>   _nodes;
  std::vector< Path >       _paths;
  std::map<int, int>        _serials_to_nodes;

  int _number_of_connections;

}; // Delinquent_network

#endif // NETWORK_TYPES_H
