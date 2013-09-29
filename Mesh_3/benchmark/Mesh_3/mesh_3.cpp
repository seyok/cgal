int EXIT1, EXIT2, EXIT3, BASE1, BASE2, BASE3, BASE4, BASE5, BASE6, BASE7, BASE8,  BASE9, BASE10, CALLS;

//#define ADD_BBOX_POINTS
 //#define DOUBLE_FILTER

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>

#include <CGAL/Polyhedral_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>
#include <CGAL/refine_mesh_3.h>
#include <CGAL/bounding_box.h>
#include <CGAL/Timer.h>

// IO
#include <CGAL/IO/Polyhedron_iostream.h>

// Domain
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron, K> Mesh_domain;

// Triangulation
typedef CGAL::Mesh_triangulation_3<Mesh_domain>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;

// Criteria
typedef CGAL::Mesh_criteria_3<Tr> Mesh_criteria;

// To avoid verbose function and named parameters call
using namespace CGAL::parameters;

int main()
{
  std::cerr.precision(20);
  std::cout.precision(20);
  CGAL::default_random = CGAL::Random(0);

  EXIT1 = EXIT2 = EXIT3 = CALLS = BASE1 = BASE2 = BASE3 = BASE4 = BASE5 = BASE6 = BASE7 = BASE8 = BASE9 = BASE10 = 0;
  // Create input polyhedron
  Polyhedron polyhedron;
  std::ifstream input("data/rocker-arm.off");
  input >> polyhedron;
   
  // Create domain
  Mesh_domain domain(polyhedron);
 
  CGAL::Bbox_3 bb = bbox_3(polyhedron.points_begin(), polyhedron.points_end());
  std::cerr << "bbox(polyhedron) = " << bb << std::endl;

  // Mesh criteria (no cell_size set)
  //  Mesh_criteria criteria(facet_size=0.5111 *0.0035); // fandisk
  Mesh_criteria criteria(facet_size=0.3034 *0.0045); // rocker-arm
 
  std::cerr << "Meshing... ";
  CGAL::Timer t;
  t.start();
  // Mesh generation
  C3t3 c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());
  t.stop();
  std::cerr << t.time() << std::endl;
  std::cerr <<  BASE1 << "  " <<  BASE2 << "  " <<  BASE3 << "  " <<  BASE4 << "  " <<  BASE5 << "  " <<  BASE6 << "  " <<  BASE7 << "  " <<  BASE8 << "  " <<  BASE9 << "  " << BASE10 << std::endl;
  std::cerr << " "<< CALLS << std::endl;
  std::cerr << " "<< EXIT1 << " "<< EXIT2 << " " << EXIT3 << std::endl;

#ifdef DOUBLE_FILTER
  std::cerr << "Used double filter" << std::endl;
#endif 

#ifdef ADD_BBOX_POINTS
  std::cerr << "Added bbox points" << std::endl;
#endif

  // Output
  // std::ofstream medit_file("fandisk_CGAL.mesh");
  // c3t3.output_to_medit(medit_file);
  // medit_file.close();

  // Set tetrahedron size (keep cell_radius_edge), ignore facets
  //Mesh_criteria new_criteria(cell_radius_edge=3, cell_size=0.03);

  // Mesh refinement
  //CGAL::refine_mesh_3(c3t3, domain, new_criteria);

  // Output
  //medit_file.open("out_2.mesh");
  //c3t3.output_to_medit(medit_file);

  return 0;
}
