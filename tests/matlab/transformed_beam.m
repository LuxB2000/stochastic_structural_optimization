function [ output_args ] = transformed_beam( path, verbose )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
%
%       p2
%     /
%    /
%   /
%   p1

%% defining the structure
% nodes
p1 = [1,2,3];
p2 = [2,1,5];

% structural properties of the beams
E = 1;
A = 2300E-6; % in m^2
Iy = 1;  % TODO: need to find real values
Iz = 1;  % TODO: need to find real values
Iyz = 0; % TODO: need to find real values
GJ = 0;    % TODO: need to find real values
alpha = 0; % in degrees

% topology of the 
beam_start_pt = [p1];
beam_end_pt = [p2];
% the structure is not cyclic
cyclic = 0;

% external force applied on the structure
fext = []; % force at point 2, along the direction Y, amplitude: -5E3

% supports and constraints
sup = [];

% constructing the data
beams = init_data(beam_start_pt, beam_end_pt, E, A, Iy, Iz, Iyz, GJ, alpha);
%% solve the system
i = 1;
a = sqrt( sum( (beams.end_pt(i,:)-beams.start_pt(i,:)).^2 ) );
[ko,~,Co]=FR_Beam_Element(...
        beams.EA(i),beams.EIy(i),beams.EIyz(i),beams.EIz(i),beams.GJ(i),...
        0,0,0,0,0,0,... % NOT USED SO FAR
        beams.alpha(i),0,0,0,0,0,0, a, beams.start_pt(i,:), beams.end_pt(i,:));


%% save the resultes
save(strcat(path,'\Kg_transformed_beam.mat'), 'ko', '-ascii');
save(strcat(path,'\C_transformed_beam.mat'), 'Co', '-ascii');


end

