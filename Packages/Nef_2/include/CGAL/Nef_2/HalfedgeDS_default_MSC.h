// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: $
// release_date  : $CGAL_Date: $
//
// file          : HalfedgeDS_default.h
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// package       : $CGAL_Package: HalfedgeDS_2 3.1 (26 Mar 1999) $
// source        : hds.fw
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>
//
// coordinator   : MPI Saarbruecken (Stefan Schirra <stschirr@mpi-sb.mpg.de>)
//
// Halfedge Data Structure Default Implementation for CGAL.
// ============================================================================

#ifndef CGAL_HALFEDGEDS_DEFAULT_MSC_H
#define CGAL_HALFEDGEDS_DEFAULT_MSC_H 1

#include <CGAL/basic.h>
#include <CGAL/In_place_list.h>
#include <CGAL/Nef_2/HalfedgeDS_items_decorator.h>
#include <CGAL/Nef_2/HDS_items_MSC.h>
#include <CGAL/Hash_map.h>
#include <iterator>

CGAL_BEGIN_NAMESPACE

template < class Vertex_base>
class HalfedgeDS_in_place_list_vertex
    : public Vertex_base, public CGAL::In_place_list_base<
                      HalfedgeDS_in_place_list_vertex< Vertex_base> > {
public:
    typedef HalfedgeDS_in_place_list_vertex< Vertex_base> Self;
    typedef typename Vertex_base::Vertex_handle       Vertex_handle;
    typedef typename Vertex_base::Vertex_const_handle Vertex_const_handle;
    HalfedgeDS_in_place_list_vertex() {}                     // down cast
    HalfedgeDS_in_place_list_vertex( const Vertex_base& v)
        : Vertex_base(v) {}
    Self& operator=( const Self& v) {
        // This self written assignment avoids that assigning vertices will
        // overwrite the list linking of the target vertex.
        *((Vertex_base*)this) = ((const Vertex_base&)v);
        return *this;
    }
};

template < class Halfedge_base>
class HalfedgeDS_in_place_list_halfedge
    : public Halfedge_base, public CGAL::In_place_list_base<
                  HalfedgeDS_in_place_list_halfedge< Halfedge_base> > {
public:
    typedef HalfedgeDS_in_place_list_halfedge< Halfedge_base> Self;
    typedef typename Halfedge_base::Halfedge_handle       Halfedge_handle;
    typedef typename Halfedge_base::Halfedge_const_handle
                                                    Halfedge_const_handle;
    HalfedgeDS_in_place_list_halfedge() {}                   // down cast
    HalfedgeDS_in_place_list_halfedge( const Halfedge_base& h)
        : Halfedge_base(h) {}
    Self& operator=( const Self& h) {
        // This self written assignment avoids that assigning halfedges will
        // overwrite the list linking of the target halfedge.
        *((Halfedge_base*)this) = ((const Halfedge_base&)h);
        return *this;
    }
};

template < class Face_base>
class HalfedgeDS_in_place_list_face
    : public Face_base, public CGAL::In_place_list_base<
                            HalfedgeDS_in_place_list_face< Face_base> > {
public:
    typedef HalfedgeDS_in_place_list_face< Face_base>  Self;
    typedef typename Face_base::Face_handle       Face_handle;
    typedef typename Face_base::Face_const_handle Face_const_handle;
    HalfedgeDS_in_place_list_face() {}                   // down cast
    HalfedgeDS_in_place_list_face( const Face_base& f) : Face_base(f) {}
    Self& operator=( const Self& f) {
        // This self written assignment avoids that assigning faces will
        // overwrite the list linking of the target face.
        *((Face_base*)this) = ((const Face_base&)f);
        // this->Face_base::operator=(f); // does not compile on SGI
        return *this;
    }
};

template <class Traits_>
class HalfedgeDS_ipl_MSC_base {
public:
  typedef HalfedgeDS_ipl_MSC_base<Traits_> Self;
  typedef Traits_  Traits;

  typedef CGALMSC::Vertex_<Self,Traits>   Vertex_base;
  typedef CGALMSC::Halfedge_<Self,Traits> Halfedge_base;
  typedef CGALMSC::Face_<Self,Traits>     Face_base;

  typedef HalfedgeDS_in_place_list_vertex<Vertex_base> Vertex;
  typedef CGAL::In_place_list<Vertex,false>            Vertex_list;
  typedef CGAL::CGALi::In_place_list_iterator<Vertex>  Vertex_handle;
  typedef CGAL::CGALi::In_place_list_iterator<Vertex>  Vertex_iterator;
  typedef CGAL::CGALi::In_place_list_const_iterator<Vertex> 
      Vertex_const_handle;
  typedef CGAL::CGALi::In_place_list_const_iterator<Vertex> 
      Vertex_const_iterator;

  typedef HalfedgeDS_in_place_list_vertex<Halfedge_base> Halfedge;
  typedef CGAL::In_place_list<Halfedge,false>            Halfedge_list;
  typedef CGAL::CGALi::In_place_list_iterator<Halfedge>  Halfedge_handle;
  typedef CGAL::CGALi::In_place_list_iterator<Halfedge>  Halfedge_iterator;
  typedef CGAL::CGALi::In_place_list_const_iterator<Halfedge> 
      Halfedge_const_handle;
  typedef CGAL::CGALi::In_place_list_const_iterator<Halfedge> 
      Halfedge_const_iterator;

  typedef HalfedgeDS_in_place_list_vertex<Face_base> Face;
  typedef CGAL::In_place_list<Face,false>            Face_list;
  typedef CGAL::CGALi::In_place_list_iterator<Face>  Face_handle;
  typedef CGAL::CGALi::In_place_list_iterator<Face>  Face_iterator;
  typedef CGAL::CGALi::In_place_list_const_iterator<Face> 
      Face_const_handle;
  typedef CGAL::CGALi::In_place_list_const_iterator<Face> 
      Face_const_iterator;

};



template < class Traits_>
class HalfedgeDS_ipl_MSC : 
  public HalfedgeDS_ipl_MSC_base<Traits_> {
public:
  typedef Traits_  Traits;
  typedef HalfedgeDS_ipl_MSC_base<Traits_> Base;
  typedef HalfedgeDS_ipl_MSC<Traits_> Self;

  typedef typename Base::Vertex_base Vertex_base;
  typedef typename Base::Vertex Vertex;
  typedef typename Base::Vertex_list Vertex_list;
  typedef typename Base::Vertex_handle Vertex_handle;
  typedef typename Base::Vertex_const_handle Vertex_const_handle;
  typedef typename Base::Vertex_iterator Vertex_iterator;
  typedef typename Base::Vertex_const_iterator Vertex_const_iterator;

  typedef typename Base::Halfedge_base Halfedge_base;
  typedef typename Base::Halfedge Halfedge;
  typedef typename Base::Halfedge_list Halfedge_list;
  typedef typename Base::Halfedge_handle Halfedge_handle;
  typedef typename Base::Halfedge_const_handle Halfedge_const_handle;
  typedef typename Base::Halfedge_iterator Halfedge_iterator;
  typedef typename Base::Halfedge_const_iterator Halfedge_const_iterator;

  typedef typename Base::Face_base Face_base;
  typedef typename Base::Face Face;
  typedef typename Base::Face_list Face_list;
  typedef typename Base::Face_handle Face_handle;
  typedef typename Base::Face_const_handle Face_const_handle;
  typedef typename Base::Face_iterator Face_iterator;
  typedef typename Base::Face_const_iterator Face_const_iterator;

  typedef typename Halfedge_list::size_type          size_type;
  typedef typename Halfedge_list::difference_type    difference_type;
  typedef std::bidirectional_iterator_tag            iterator_category;
  typedef CGAL::Tag_true                             Supports_removal;

  typedef typename Vertex::Supports_vertex_halfedge   Supports_vertex_halfedge;
  typedef typename Halfedge::Supports_halfedge_prev   Supports_halfedge_prev;
  typedef typename Halfedge::Supports_halfedge_vertex Supports_halfedge_vertex;
  typedef typename Halfedge::Supports_halfedge_face   Supports_halfedge_face;
  typedef typename Face::Supports_face_halfedge       Supports_face_halfedge;

    // Halfedges are allocated in pairs. Here is the type for that.
    struct Halfedge_pair {
        Halfedge first, second;
        Halfedge_pair() {}
        Halfedge_pair( const Halfedge& h, const Halfedge& g)
            : first(h), second(g) {}
    };

    static inline Vertex_handle vertex_handle( Vertex_base* v) {
        Vertex* vv = 0;
        vv = (Vertex*)((char*) v - (ptrdiff_t)((Vertex_base*)vv));
        return vv;
    }
    static inline
    Vertex_const_handle vertex_handle( const Vertex_base* v) {
        const Vertex* vv = 0;
        vv = (const Vertex*)((const char*) v -
                 (ptrdiff_t)((const Vertex_base*)vv));
        return vv;
    }

    static inline Halfedge_handle halfedge_handle( Halfedge_base* h) {
        Halfedge* hh = 0;
        hh = (Halfedge*)((char*) h - (ptrdiff_t)((Halfedge_base*)hh));
        return hh;
    }
    static inline
    Halfedge_const_handle halfedge_handle( const Halfedge_base* h) {
        const Halfedge* hh = 0;
        hh = (const Halfedge*)((const char*) h -
                 (ptrdiff_t)((const Halfedge_base*)hh));
        return hh;
    }

    static inline Face_handle face_handle( Face_base* f) {
        Face* ff = 0;
        ff = (Face*)((char*) f - (ptrdiff_t)((Face_base*)ff));
        return ff;
    }
    static inline
    Face_const_handle face_handle( const Face_base* h) {
        const Face* ff = 0;
        ff = (const Face*)((const char*)f - (ptrdiff_t)((const Face_base*)ff));
        return ff;
    }

protected:
    Vertex_list        vertices;
    Halfedge_list      halfedges;
    Face_list          faces;

    size_type          nb_border_halfedges;
    size_type          nb_border_edges;
    Halfedge_iterator  border_halfedges;

// CREATION

private:
    void pointer_update( const Self& hds);
        // Update own pointers assuming that they lived previously
        // in a halfedge data structure `hds' with lists.

public:
    HalfedgeDS_ipl_MSC() 
      : Base(), nb_border_halfedges(0), nb_border_edges(0) {}

    HalfedgeDS_ipl_MSC(size_type, size_type, size_type)
        : Base(), nb_border_halfedges(0), nb_border_edges(0) {}
      // not used here.

    ~HalfedgeDS_ipl_MSC() { erase_all(); }

    HalfedgeDS_ipl_MSC(const Self& hds)
    :  vertices( hds.vertices),
       halfedges( hds.halfedges),
       faces( hds.faces),
       nb_border_halfedges( hds.nb_border_halfedges),
       nb_border_edges( hds.nb_border_edges),
       border_halfedges( hds.border_halfedges)
    { pointer_update( hds); }

    Self& operator=( const Self& hds)  {
        if ( this != &hds) {
            erase_all();
            vertices            = hds.vertices;
            halfedges           = hds.halfedges;
            faces               = hds.faces;
            nb_border_halfedges = hds.nb_border_halfedges;
            nb_border_edges     = hds.nb_border_edges;
            border_halfedges    = hds.border_halfedges;
            pointer_update( hds);
        }
        return *this;
    }

    void reserve( size_type, size_type, size_type) {}
        // function is void here.

// Access Member Functions

    size_type size_of_vertices() const  { return vertices.size();}
    size_type size_of_halfedges() const { return halfedges.size();}
        // number of all halfedges (including border halfedges).
    size_type size_of_faces() const     { return faces.size();}

    size_type capacity_of_vertices() const    { return vertices.max_size();}
    size_type capacity_of_halfedges() const   { return halfedges.max_size();}
    size_type capacity_of_faces() const       { return faces.max_size();}

    size_t bytes() const {
        return sizeof(Self)
               + vertices.size()  * sizeof( Vertex)
               + halfedges.size() * sizeof( Halfedge)
               + faces.size()     * sizeof( Face);
    }
    size_t bytes_reserved() const { return bytes();}

    Vertex_iterator   vertices_begin()   { return vertices.begin();}
    Vertex_iterator   vertices_end()     { return vertices.end();}
    Halfedge_iterator halfedges_begin()  { return halfedges.begin();}
    Halfedge_iterator halfedges_end()    { return halfedges.end();}
    Face_iterator     faces_begin()      { return faces.begin();}
    Face_iterator     faces_end()        { return faces.end();}

    // The constant iterators and circulators.

    Vertex_const_iterator   vertices_begin()  const{ return vertices.begin();}
    Vertex_const_iterator   vertices_end()    const{ return vertices.end();}
    Halfedge_const_iterator halfedges_begin() const{ return halfedges.begin();}
    Halfedge_const_iterator halfedges_end()   const{ return halfedges.end();}
    Face_const_iterator     faces_begin()     const{ return faces.begin();}
    Face_const_iterator     faces_end()       const{ return faces.end();}

// Insertion
//
// The following operations simply allocate a new element of that type.
// Halfedges are always allocated in pairs of opposite halfedges. The
// opposite pointers are automatically set.

    Vertex_handle vertices_push_back( const Vertex& v) {
        vertices.push_back( * new Vertex(v));
        Vertex_handle vh = vertices.end();
        return --vh;
    }

    Halfedge_handle edges_push_back( const Halfedge& h, const Halfedge& g) {
        // creates a new pair of opposite border halfedges.
        Halfedge_pair* hpair = new Halfedge_pair( h, g);
        Halfedge* h2 = &(hpair->first);
        Halfedge* g2 = &(hpair->second);
        CGAL_assertion( h2 == (Halfedge*)hpair);
        CGAL_assertion( g2 == h2 + 1);
        h2->set_opposite(g2);
        g2->set_opposite(h2);
        halfedges.push_back( *h2);
        Halfedge_handle hh = halfedges.end();
        --hh;
        halfedges.push_back( *g2);
        return hh;
    }

    Halfedge_handle edges_push_back( const Halfedge& h) {
        CGAL_precondition( h.opposite() != Halfedge_const_handle());
        return edges_push_back( h, *(h.opposite()));
    }

    Face_handle faces_push_back( const Face& f) {
        faces.push_back( * new Face(f));
        Face_handle fh = faces.end();
        return --fh;
    }


// Removal
//
// The following operations erase an element referenced by a handle.
// Halfedges are always deallocated in pairs of opposite halfedges. Erase
// of single elements is optional. The deletion of all is mandatory.

    void vertices_pop_front() {
        Vertex* v = &(vertices.front());
        vertices.pop_front();
        delete v;
    }
    void vertices_pop_back() {
        Vertex* v = &(vertices.back());
        vertices.pop_back();
        delete v;
    }
    void vertices_erase( Vertex_handle v) {
        vertices.erase(v);
        delete &*v;
    }
    void vertices_erase( Vertex_iterator first, Vertex_iterator last) {
        while (first != last)
            vertices_erase(first++);
    }

    void edges_erase( Halfedge_handle h) {
        // deletes the pair of opposite halfedges h and h->opposite().
        Halfedge_handle g = h->opposite();
        halfedges.erase(h);
        halfedges.erase(g);
        Halfedge_pair* hpair = (Halfedge_pair*)(&*h);
        if ( &*h > &*g)
            hpair = (Halfedge_pair*)(&*g);
        CGAL_assertion( &(hpair->first) == (Halfedge*)hpair);
        delete hpair;
    }
    void edges_pop_front() { edges_erase( halfedges.begin()); }
    void edges_pop_back()  {
        Halfedge_iterator h = halfedges.end();
        edges_erase( --h);
    }
    void edges_erase( Halfedge_iterator first, Halfedge_iterator last) {
        while (first != last) {
	    Halfedge_iterator tmp = first;
            ++first;
            CGAL_assertion( first != last);
            ++first;
            edges_erase(tmp);
        }
    }

    void faces_pop_front() {
        Face* f = &(faces.front());
        faces.pop_front();
        delete f;
    }
    void faces_pop_back() {
        Face* f = &(faces.back());
        faces.pop_back();
        delete f;
    }
    void faces_erase( Face_handle f) {
        faces.erase(f);
        delete &*f;
    }
    void faces_erase( Face_iterator first, Face_iterator last) {
        while (first != last)
            faces_erase(first++);
    }

    void erase_all() {
        vertices.destroy();
        edges_erase( halfedges.begin(), halfedges.end());
        faces.destroy();
        nb_border_halfedges = 0;
        nb_border_edges = 0;
        border_halfedges = Halfedge_handle();
    }

// Operations with Border Halfedges

    size_type size_of_border_halfedges() const { return nb_border_halfedges;}
        // number of border halfedges. An edge with no incident face
        // counts as two border halfedges. Precondition: `normalize_border()'
        // has been called and no halfedge insertion or removal and no
        // change in border status of the halfedges have occured since
        // then.

    size_type size_of_border_edges() const { return nb_border_edges;}
        // number of border edges. If `size_of_border_edges() ==
        // size_of_border_halfedges()' all border edges are incident to a
        // face on one side and to a hole on the other side.
        // Precondition: `normalize_border()' has been called and no
        // halfedge insertion or removal and no change in border status of
        // the halfedges have occured since then.

    Halfedge_iterator border_halfedges_begin() {
        // halfedge iterator starting with the border edges. The range [
        // `halfedges_begin(), border_halfedges_begin()') denotes all
        // non-border edges. The range [`border_halfedges_begin(),
        // halfedges_end()') denotes all border edges. Precondition:
        // `normalize_border()' has been called and no halfedge insertion
        // or removal and no change in border status of the halfedges have
        // occured since then.
        CGAL_postcondition( border_halfedges != Halfedge_iterator());
        return border_halfedges;
    }

    Halfedge_const_iterator border_halfedges_begin() const {
        CGAL_postcondition( border_halfedges != Halfedge_iterator());
        return border_halfedges;
    }

    void normalize_border();
        // sorts halfedges such that the non-border edges precedes the
        // border edges. For each border edge that is incident to a face
        // the halfedge iterator will reference the halfedge incident to
        // the face right before the halfedge incident to the hole.
};

// A class for comparing handles, used in the maps below.
template < class Handle>
struct _HDS_Cmp_handle {
    bool operator()( Handle a, Handle b) const { return &*a < &*b; }
};

template < class p_Traits>
void
HalfedgeDS_ipl_MSC<p_Traits>::
pointer_update( const HalfedgeDS_ipl_MSC<p_Traits>& hds) {
    // Update own pointers assuming that they lived previously
    // in a halfedge data structure `hds' with lists.
    typedef CGAL::Hash_map<Vertex_const_handle,Vertex_handle>     V_map;
    typedef CGAL::Hash_map<Halfedge_const_handle,Halfedge_handle> H_map;
    typedef CGAL::Hash_map<Face_const_handle,Face_handle>         F_map;
    V_map v_map;
    H_map h_map;
    F_map f_map;
    h_map[Halfedge_const_iterator()] = Halfedge_iterator();
    v_map[Vertex_const_iterator()]   = Vertex_iterator();
    f_map[Face_const_iterator()]     = Face_iterator();
    // initialize maps.
    Halfedge_iterator ii = halfedges_begin();
    Halfedge_const_iterator i = hds.halfedges_begin();
    for ( ; i != hds.halfedges_end(); ++i) {
        h_map[i] = ii;
        ++ii;
    }
    h_map[i] = ii;
    if ( CGAL::check_tag( Supports_halfedge_vertex())) {
        Vertex_iterator vv = vertices_begin();
        for ( Vertex_const_iterator v = hds.vertices_begin();
              v != hds.vertices_end(); ++v) {
            v_map[v] = vv;
            ++vv;
        }
    }
    if ( CGAL::check_tag( Supports_halfedge_face())) {
        Face_iterator ff = faces_begin();
        for ( Face_const_iterator f = hds.faces_begin();
              f != hds.faces_end(); ++f) {
            f_map[f] = ff;
            ++ff;
        }
    }
    HalfedgeDS_items_decorator<Self> D;
    for ( Halfedge_iterator h = halfedges_begin(); h != halfedges_end(); ++h) {
        h->set_next( h_map[ h->next()]);
        h->set_opposite( h_map[ h->opposite()]);
        if ( CGAL::check_tag( Supports_halfedge_prev()))
            D.set_prev( h, h_map[ D.get_prev(h)]);
        if ( CGAL::check_tag( Supports_halfedge_vertex())) {
            D.set_vertex( h, v_map[ D.get_vertex(h)]);
            D.set_vertex_halfedge( h);
        }
        if ( h->is_border())
            D.set_face( h, Face_handle());
        else if ( CGAL::check_tag( Supports_halfedge_face())) {
            D.set_face( h, f_map[ D.get_face(h)]);
            D.set_face_halfedge( h);
        }
    }
    border_halfedges = h_map[ border_halfedges];
}

template < class p_Traits>
void
HalfedgeDS_ipl_MSC<p_Traits>::
normalize_border() {
    CGAL_assertion_code( size_t count = halfedges.size();)
    nb_border_halfedges = 0;
    nb_border_edges = 0;
    Halfedge_list  border;
    Halfedge_iterator i = halfedges_begin();
    while ( i != halfedges_end()) {
        Halfedge_iterator j = i;
        ++i;
        ++i;
        Halfedge_iterator k = j;
        ++k;
        if ( j->is_border()) {
            nb_border_halfedges++;
            nb_border_edges++;
            if (k->is_border())
                nb_border_halfedges++;
            border.splice( border.end(), halfedges, k);
            border.splice( border.end(), halfedges, j);
        } else if ( k->is_border()) {
            nb_border_halfedges++;
            nb_border_edges++;
            border.splice( border.end(), halfedges, j);
            border.splice( border.end(), halfedges, k);
        } else {
            CGAL_assertion_code( count -= 2;)
        }
    }
    CGAL_assertion( count == 2 * nb_border_edges );
    CGAL_assertion( count == border.size());
    if ( i == halfedges_begin()) {
        halfedges.splice( halfedges.end(), border);
        i = halfedges_begin();
    } else {
        --i;
        --i;
        CGAL_assertion( ! i->is_border() && ! i->opposite()->is_border());
        halfedges.splice( halfedges.end(), border);
        ++i;
        ++i;
    }
    CGAL_assertion( i == halfedges_end() || i->opposite()->is_border());
    border_halfedges = i;
}

template <class p_Traits> 
class HalfedgeDS_default_MSC
  : public HalfedgeDS_ipl_MSC< p_Traits> {
public:
  typedef p_Traits Traits;
  typedef size_t size_type;
  HalfedgeDS_default_MSC() {}
  HalfedgeDS_default_MSC( size_type v, size_type h, size_type f)
    : HalfedgeDS_ipl_MSC< p_Traits>(v,h,f) {}
};

CGAL_END_NAMESPACE

#endif // CGAL_HALFEDGEDS_DEFAULT_MSC_H 
