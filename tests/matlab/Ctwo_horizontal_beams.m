function [] = Ctwo_horizontal_beams(data_path,verbose)
% Create a simple scenario with 2 horizontal beams and 3 nodes:
%
%           |
%           | 5kN
%           \/
%  p1       p2       p3
%  ___________________
%  |                 |       
%////               ///
% <---------><------->
%    2m         2m

%% defining the structure
% nodes
p1 = [0,0,0];
p2 = [2,0,0];
p3 = [4,0,0];

% structural properties of the beams
% value are defined to match the BASIC_C in Material.h
E = 1.1;
A = 23E-4; % in m^2
Iy = 1.2;
Iz = 1.3;
Iyz = 0; % TODO: need to find real values
GJ = 1.4;
alpha = 0; % in degrees

% topology of the 
beam_start_pt = [p1; p2];
beam_end_pt = [p2; p3];

% the structure is not cyclic
cyclic = 0;

% external force applied on the structure
fext = [2,2,-5E3]; % force at point 2, along the direction Y, amplitude: -5E3

% supports and constraints
sup = [[1,1];[1,2];[1,3];[1,4];[1,5];[1,6];...
       [3,1];[3,2];[3,3];[3,4];[3,5];[3,6]];

% constructing the data
beams = init_data(beam_start_pt, beam_end_pt, E, A, Iy, Iz, Iyz, GJ, alpha);
%% solve the system
[d,felem,fsup,K] = solve_structure(beams,fext,sup,cyclic,verbose);
felem = felem(:);
%% save the resultes
if( ispc() == 1 )
    p='\';
else
    p='/';
end
save(strcat(data_path,p,'Kg_Ctwo_horizontal_beams.mat'), 'K', '-ascii');
save(strcat(data_path,p,'disp_Ctwo_horizontal_beams.mat'), 'd', '-ascii');
save(strcat(data_path,p,'fsup_Ctwo_horizontal_beams.mat'), 'fsup', '-ascii');
save(strcat(data_path,p,'felem_Ctwo_horizontal_beams.mat'), 'felem', '-ascii');

%% display the results
if(verbose)
    fprintf('Support forces in global cooridnates:\n');
    disp(fsup);
    fprintf('Nodal displacements in local coordinates:\n');
    disp(delem);
    fprintf('Element forces in local coodinates:\n');
    disp(felem);
end


end

