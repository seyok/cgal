/*!
\ingroup PkgStraightSkeleton2Concepts
\cgalConcept

The concept `StraightSkeletonHalfedge_2` describes the 
requirements for the halfedge type of the 
`StraightSkeleton_2` concept. It is a refinement of the 
`HalfedgeDSHalfedge` concept. 
The `StraightSkeletonHalfedge_2` concept requires no geometric embedding at all. The only geometric embedding used by the Straight Skeleton Data Structure are the 2D points in the contour and skeleton vertices. However, for any halfedge, there is a 2D segment implicitly given by its `source` and `target` vertices. 

\cgalRefines `HalfedgeDSHalfedge` 

\cgalHasModel CGAL::Straight_skeleton_halfedge_base_2

\sa `StraightSkeleton_2` 
\sa `StraightSkeletonHalfedge_2` 
\sa `CGAL::Straight_skeleton_vertex_base_2<Refs,Point,FT>` 
\sa `CGAL::Straight_skeleton_halfedge_base_2<Refs>` 

*/

class StraightSkeletonHalfedge_2 {
public:

/// \name Creation 
/// @{

/*!
Default Constructor. 
*/ 
StraightSkeletonHalfedge_2(); 

/*!
Constructs a halfedge with ID `id`. 

It is the links to other halfedges what determines if this is a contour edge, a contour-skeleton edge or an inner-skeleton edge. 
*/ 
StraightSkeletonHalfedge_2( int id ); 

/// @} 

/// \name Access Functions 
/// @{

/*!

*/ 
Halfedge_handle defining_contour_edge(); 

/*!
If this is a bisector halfedge, returns a handle to the inward-facing (non-border) contour halfedge corresponding to the defining contour edge which is to its left; if this is a contour halfedge, returns a handle to itself if `is\_border()` is `false`, or to its opposite if it is `true`. 
*/ 
Halfedge_const_handle defining_contour_edge() const; 

/// @} 

/// \name Queries 
/// @{

/*!
Returns `true` iff this is a bisector (or skeleton) halfedge (i.e.\ is not a contour halfedge). 
*/ 
bool is_bisector() const; 

/*!
Returns `true` iff this is a bisector and is inner (i.e.\ is not incident upon a contour vertex). 
*/ 
bool is_inner_bisector() const; 

/// @}

}; /* end StraightSkeletonHalfedge_2 */
