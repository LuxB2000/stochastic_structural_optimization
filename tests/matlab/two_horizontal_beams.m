function [ output_args ] = two_horizontal_beams( data_path, verbose )
% Create a simple scenario with 2 horizontal beams and 3 nodes:
%
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
% value are defined to match the BASIC in Material.h
E = 1;
A = 2300E-6; % in m^2
Iy = 1; 
Iz = 1; 
Iyz = 0;
GJ = 0;
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
[~,delem,felem,fsup,K] = solve_structure(beams,fext,sup,cyclic,verbose);

%% save the resultes
if( ispc() == 1 )
	save(strcat(data_path,'\Kg_two_horizontal_beams.mat'), 'K', '-ascii');
else
	save(strcat(data_path,'/Kg_two_horizontal_beams.mat'), 'K', '-ascii');
end


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

