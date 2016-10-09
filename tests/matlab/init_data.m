function [ beams ] = init_data( start_pt, end_pt, E, A, Iy, Iz, Iyz, GJ, alpha )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

alpha=alpha + zeros(size(start_pt,1),1); 
EA = E * A + zeros(size(alpha));
EIy = E * Iy + zeros(size(alpha));
EIz = E * Iz + zeros(size(alpha));
EIyz = E * Iyz + zeros(size(alpha));
GJ = GJ + zeros(size(alpha));

beams = struct;
beams.start_pt = start_pt;
beams.end_pt = end_pt;
beams.alpha = alpha;
beams.EA   = EA;
beams.EIy  = EIy;
beams.EIz  = EIz;
beams.EIyz = EIyz;
beams.GJ   = GJ;

end

