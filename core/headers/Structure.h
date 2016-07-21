/*
 * =====================================================================================
 *
 *       Filename:  Structure.h
 *
 *    Description:  Object representing the building structure.
 *			A structure is defined a set of frames, each frame is composed of 
 *			trusses or beams. Each Structure has an origin.
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:04:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_STRUCTURE_H
#define sso_STRUCTURE_H

#include "Point.h"
#include "Simple3TrussFrame.h"

class Structure{
public:
	Structure();
	Structure(Point* origin);
	~Structure();

	// setter
	void SetOrigin(Point* new_origin){ m_origin = new_origin;}
	void SetNumberOfFrames(unsigned int nbrF){m_inputNbrOfFrames = nbrF;}
	// we assume that all the frames use the same parameters
	void SetFrameParameters(const FrameParametersVectorType v, double crossSection, Material mat);
	// set the boundary conditions, specified by the point Ids
	void SetBoundaryConditions( const BoundaryConditionsVectorType bc);

	// getter
	Point* GetOrigin(){return m_origin;}
	const unsigned int GetNumberOfFrames(){ return m_frames->size(); }

	// Build the structure
	void Build();

	// Set the structure
	// TODO
	// void Save();

	// Get the information regards the built structure
	// Get the maximal displacement and the location
	void GetMaximalDisplacement(Point* loc, double* maxDisp);
	void GetMaximalElementlForce(Point* loc, double* maxElf);
	// TODO
	// StiffnessMatrixType GetStiffnessMatrix();

private:
	// typedef
	typedef std::vector<TrussFrame*> TrussFrameVectorType;

	void m_init();
	Point* m_origin;
	unsigned int m_inputNbrOfFrames;

	// params
	FrameParametersVectorType* m_frame_params;
	double m_crossSection;
	Material m_material_type;
	// Boundary conditions
	BoundaryConditionsVectorType* m_bc;
	// the frames of the structures
	TrussFrameVectorType* m_frames;

	static const unsigned int m_defaultNbrOfParameters = 3;

};

#endif

