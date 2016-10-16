function [d,d_lc,felem,fsup,K] = solve_structure(beams, fext, sup, cyclic, verbose)
% [D,DLC,FELEM,FSUP,K] = SOLVE_STRUCTURE(BEAMS,EXTERNAL_FORCES, SUPPORT, CYCLIC)
% outputs:
% the nodal displacements D and the element forces FELEM based
% in local coordinates. FSUP is the forces localised at the supports.
% K is the global stiffness matrix in global coordinates.
% inputs: 
% BEAM is a structure containing 
%       beam(i).start_pt : Starting pt
%       beam(i).end_pt   : ending pt
%       beam(i).alpha    : angle along X axis
%       beam(i).EA       : axial rigidity
%       beam(i).EIy      : bending stiffness
%       beam(i).EIyz     : coupled bending stiffness
%       beam(i).GJ       : Saint Venant torsionality
%
% EXTERNAL_FORCES is a 3XF matrix where each raw specifies a force with
% the point Id, the direction and the amplitude of the force
%
% SUPPORT is a Sx2 matrix where each raw specifies a support with the point
% Id and the contraint (i.e. 1=Fx, 2=Fy, ... 6=Mz)
% if the structure is cyclic, then CYCLIC=1

% Constant
NDOF = 6;

% outputs
delem = [];
felem = [];
K = [];
fsup = [];

nel = size(beams.start_pt,1);% #elements
n = nel + not(cyclic);% #points

if( verbose )
    fprintf('The structure contains %i elements and %i points.\n', nel, n);
end

% external force vect.
forces_ext=zeros(NDOF,n);
for i=1:size(fext,1)
    forces_ext(fext(i,1),fext(i,2)) = fext(i,3);
end
if( verbose )
    fprintf('Applied Forces:\n')
    disp(forces_ext)
end
forces_ext = forces_ext(:);

% support vector
support = zeros(NDOF,n);
for i=1:size(sup,1)
    support(sup(i,2),sup(i,1)) = 1;
end
if( verbose )
    fprintf('Supports:\n')
    disp(support)
end
support = support(:);

% Topology Matrix
for i=1:nel
    for j=1:2*NDOF
        edof(i,j)=(i-1)*NDOF+j;
    end
end

if( cyclic )
    % topology matrix for cyclic structure, we assume the last node is
    % connected to the first one.
    % cyclic structure: the last point is the first, the last element connect
    % p1 and p3
    for j=1:NDOF
        edof(3,j) = (2-1)*NDOF + j+NDOF; % last beam connect point 1 and 2, here connections with 3
    end
    for j=7:12
        edof(3,j) = j - NDOF;  % last beam connect point 1 and 2, here connections with 1
    end
    
end

% Build stiffness Matrix
K=zeros(NDOF*n);
M=zeros(NDOF*n);

for i=1:nel
    % ko element stiffness matrix for O in general axes
    % mo element mass matrix for O in general axes
    a = sqrt( sum( (beams.end_pt(i,:)-beams.start_pt(i,:)).^2 ) ); %/nel;
    [ko,mo]=FR_Beam_Element(...
        beams.EA(i),beams.EIy(i),beams.EIyz(i),beams.EIz(i),beams.GJ(i),...
        0,0,0,0,0,0,... % NOT USED SO FAR
        beams.alpha(i),0,0,0,0,0,0, a, beams.start_pt(i,:), beams.end_pt(i,:));
    % Global Structure stiffness and mass (referred to O in general axis YY,ZZ)
    K(edof(i,:), edof(i,:))=K(edof(i,:), edof(i,:))+ko;
    M(edof(i,:), edof(i,:))=M(edof(i,:), edof(i,:))+mo;
end

% find the active degree of freedom
active_dof = zeros( sum(not(support)), 1 );
d = 1;
for i=1:NDOF*n
    if( not(support(i)) )
        active_dof(d,1)=i;
        d = d + 1;
    end
end

% %% system solving
Kred=K(active_dof, active_dof);
Fred= forces_ext(active_dof);
% displacement
dred=inv(Kred)*Fred;
d=zeros(NDOF*n,1);
d(active_dof)=dred;

% displacements and forces on each node in local coordinates systems,
%  output of the function
delem = zeros(2*NDOF,nel); % two points per elements
felem = zeros(2*NDOF,nel);

% support forces
fsup = zeros(NDOF*n,1);
fsup = K * d;
fsup(active_dof) = 0;

% force in local coordinates
f=zeros(NDOF*n,1);
for i=1:nel
    a = sqrt( sum( (beams.end_pt(i,:)-beams.start_pt(i,:)).^2 ) ); %/nel;
    [ko,~,Co]=FR_Beam_Element(...
        beams.EA(i),beams.EIy(i),beams.EIyz(i),beams.EIz(i),beams.GJ(i),...
        0,0,0,0,0,0,... % NOT USED SO FAR
        beams.alpha(i),0,0,0,0,0,0, a, beams.start_pt(i,:), beams.end_pt(i,:));

    delem(:,i) =  Co' * d(edof(i,:));
    felem(:,i) = ko * delem(:,i);

end
d_lc = delem;