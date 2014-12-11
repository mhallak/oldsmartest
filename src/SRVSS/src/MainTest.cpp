#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "ros/ros.h"

#include "fcl/distance.h"
#include "fcl/shape/geometric_shapes.h"
#include "fcl/traversal/traversal_node_bvhs.h"

#include <boost/filesystem.hpp>


using namespace fcl;

void loadOBJFile(const char* filename, std::vector<Vec3f>& points, std::vector<Triangle>& triangles)
{

  FILE* file = fopen(filename, "rb");
  if(!file)
  {
    std::cerr << "file not exist" << std::endl;
    return;
  }

  bool has_normal = false;
  bool has_texture = false;
  char line_buffer[2000];
  while(fgets(line_buffer, 2000, file))
  {
    char* first_token = strtok(line_buffer, "\r\n\t ");
    if(!first_token || first_token[0] == '#' || first_token[0] == 0)
      continue;

    switch(first_token[0])
    {
    case 'v':
      {
        if(first_token[1] == 'n')
        {
          strtok(NULL, "\t ");
          strtok(NULL, "\t ");
          strtok(NULL, "\t ");
          has_normal = true;
        }
        else if(first_token[1] == 't')
        {
          strtok(NULL, "\t ");
          strtok(NULL, "\t ");
          has_texture = true;
        }
        else
        {
          FCL_REAL x = (FCL_REAL)atof(strtok(NULL, "\t "));
          FCL_REAL y = (FCL_REAL)atof(strtok(NULL, "\t "));
          FCL_REAL z = (FCL_REAL)atof(strtok(NULL, "\t "));
          Vec3f p(x, y, z);
          points.push_back(p);
        }
      }
      break;
    case 'f':
      {
        Triangle tri;
        char* data[30];
        int n = 0;
        while((data[n] = strtok(NULL, "\t \r\n")) != NULL)
        {
          if(strlen(data[n]))
            n++;
        }

        for(int t = 0; t < (n - 2); ++t)
        {
          if((!has_texture) && (!has_normal))
          {
            tri[0] = atoi(data[0]) - 1;
            tri[1] = atoi(data[1]) - 1;
            tri[2] = atoi(data[2]) - 1;
          }
          else
          {
            const char *v1;
            for(int i = 0; i < 3; i++)
            {
              // vertex ID
              if(i == 0)
                v1 = data[0];
              else
                v1 = data[t + i];

              tri[i] = atoi(v1) - 1;
            }
          }
          triangles.push_back(tri);
        }
      }
      break;
    }
  }
}


int main(int argc, char** argv)
{
	std::cout << " I start !!! " << std::endl;

	std::vector<Vec3f> o1_vertices, o2_vertices;
	std::vector<Triangle> o1_triangles, o2_triangles;
/*
	Vec3f o1_v1(0,0,0), o1_v2(1,0,0), o1_v3(0,1,0), o1_v4(0,0,1);
	Triangle o1_t1(1,2,4), o1_t2(1,3,4), o1_t3(1,2,3), o1_t4(2,3,4);
	o1_vertices.push_back(o1_v1); o1_vertices.push_back(o1_v2); o1_vertices.push_back(o1_v3); o1_vertices.push_back(o1_v4);
	o1_triangles.push_back(o1_t1); o1_triangles.push_back(o1_t2); o1_triangles.push_back(o1_t3); o1_triangles.push_back(o1_t4);

	Vec3f o2_v1(0,0,0), o2_v2(1,0,0), o2_v3(0,1,0), o2_v4(0,0,1);
	Triangle o2_t1(1,2,4), o2_t2(1,3,4), o2_t3(1,2,3), o2_t4(2,3,4);
	o2_vertices.push_back(o2_v1); o2_vertices.push_back(o2_v2); o2_vertices.push_back(o2_v3); o2_vertices.push_back(o2_v4);
	o2_triangles.push_back(o2_t1); o2_triangles.push_back(o2_t2); o2_triangles.push_back(o2_t3); o2_triangles.push_back(o2_t4);
*/

	  boost::filesystem::path path("/home/userws3/Desktop/Link to SRVSS/world_components_models");
	  loadOBJFile((path / "body_lite.obj").string().c_str(), o1_vertices, o1_triangles);
	  loadOBJFile((path / "barrel1.obj").string().c_str(), o2_vertices, o2_triangles);

	  BVHModel<RSS> * m1 = new BVHModel<RSS>();
	  BVHModel<RSS> * m2 = new BVHModel<RSS>();

	  m1->beginModel();
	  m1->addSubModel(o1_vertices, o1_triangles);
	  m1->endModel();

	  m2->beginModel();
	  m2->addSubModel(o2_vertices, o2_triangles);
	  m2->endModel();

	  DistanceResult local_result1, local_result2,local_result3, local_result4;
	  Transform3f pose1, pose2;

	  Vec3f translation1(0,5000,5000), translation2(5000,0,5000), translation3(5000,5000,0), translation4(5000,5000,5000);

	  pose1.setTranslation(translation1);
	  distance(m1,pose1,m2,pose2,20,local_result1);
	  std::cout << "dist1 = " << local_result1.min_distance/1000 << std::endl;
	  std::cout << local_result1.nearest_points[0][0] << "  " << local_result1.nearest_points[0][1] << "  " << local_result1.nearest_points[0][2] << std::endl;
	  std::cout << local_result1.nearest_points[1][0] << "  " << local_result1.nearest_points[1][1] << "  " << local_result1.nearest_points[1][2] << std::endl;

	  pose1.setTranslation(translation2);
	  distance(m1,pose1,m2,pose2,20,local_result2);
	  std::cout << "dist2 = " << local_result2.min_distance/1000 << std::endl;

	  pose1.setTranslation(translation3);
	  distance(m1,pose1,m2,pose2,20,local_result3);
	  std::cout << "dist3 = " << local_result3.min_distance/1000 << std::endl;

	  pose1.setTranslation(translation4);
	  distance(m1,pose1,m2,pose2,20,local_result4);
	  std::cout << "dist4 = " << local_result4.min_distance/1000 << std::endl;
	  std::cout << local_result4.nearest_points[0][0] << "  " << local_result4.nearest_points[0][1] << "  " << local_result4.nearest_points[0][2] << std::endl;
	  std::cout << local_result4.nearest_points[1][0] << "  " << local_result4.nearest_points[1][1] << "  " << local_result4.nearest_points[1][2] << std::endl;



	  std::cout << " I finish !!! " <<std::endl;

	return 0;
}

