//
// Created by plumat on 4/6/16.
//
// A InternalTrussObject is a structure that consists of axial members connected by pin joints. Here we consider 3D Truss.
// The loads on a InternalTrussObject are assumed to be concentrated at the joints.
// The members of a InternalTrussObject support the external load through _axial force_ as they do not undergo bending deformation.
// Therefore, no bending moments are present in InternalTrussObject members.
//
// A truss is characterised by
// - 2 points (2 joints, from which we deduce its length L=sqrt((p1_x-p2_x)^2+(p1_y-p2_y)^2+(p1_z-p2_z)^2),
// - a cross section A,
// - Young’s modulus E (specified by the material).
//
// Axial direction is consider to be the local x_l direction. So, the displacements in direction y_l and z_l are null.
//
// Due to restrictions applied to the InternalTrussObject elements, the only displacements/forces to take into considerations are
// U_i,V_i,W_i per node i along the three global axis x_g,y_g,z_g respectively.
// Since each InternalTrussObject is defined with 2 nodes, then 6 displacements/forces are to consider in global system.
//

#ifndef SSO_TRUSS_H
#define SSO_TRUSS_H

#include <vector>

#include "StructuralElement.h"
#include "Types.h"
#include "Material.h"

class InternalTrussObject: StructuralElement {
public:
    // enum and typedef
    //enum material {BASIC,TEST}; // possible materials

    // constructors and destructor
    // cross section is given in mm^2
    InternalTrussObject(Point* starting_pt, Point* ending_pt, double cross_section, Material type_material);
    ~InternalTrussObject();

    // getters
    StiffnessMatrixType*      GetLocalStiffnessMatrixPointer();
    const StiffnessMatrixType GetLocalStiffnessMatrix();

    TransformationMatrixType*       GetLocalTransformationMatrixPointer();
    const TransformationMatrixType  GetLocalTransformationMatrix();

    double GetLength(){return m_L;}
    double GetCrossSection(){return m_A;}
    double GetYoungModulus(){return m_E;}

		// getters
		// all give information in local coordinates
		DisplacementVectorType GetNodeDisplacements(){
			return DisplacementVectorType(*m_disp_local_coord);
		}
		DisplacementVectorType* GetNodeDisplacementsPointer(){
			return m_disp_local_coord;
		}
    const ForceVectorType GetInternalForces(){
			return ForceVectorType(*m_f);
		}
    ForceVectorType* GetInternalForcesPointer(){
			return m_f;
		}

    // setters
    //void SetInternalForces();
    void SetNodalDisplacementInGlobalCoordinates(DisplacementVectorType disp);

private:
    double m_A, m_E, m_L;
    Material m_material;
    Point *m_start_p, *m_end_p;
    DisplacementVectorType *m_disp_local_coord;
    ForceVectorType *m_f;
    StiffnessMatrixType      *m_k;
    TransformationMatrixType *m_c;
    ForceVectorType m_internalForces;
};


#endif //SSO_TRUSS_H
