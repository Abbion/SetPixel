#include "spGfxShapes.h"
#include "spGfxLine.h"
#include "spAlgorithms.h"
#include <iostream>


//-----------------------------------------------------
sp::BitMap sp::Triangle(const sp::vector2f& p1, const sp::vector2f& p2, const sp::vector2f& p3)
{
   sp::BitMap bm;
   if(!sp::coordConverter::pointInView(p1) && !sp::coordConverter::pointInView(p2) && !sp::coordConverter::pointInView(p3))
      return bm;

   sp::BitMap triangle_sides[3] = {sp::line(p1, p2), sp::line(p2, p3), sp::line(p3, p1)};
   bm.marge(triangle_sides, 3);
   return bm;
}

sp::BitMap sp::Triangle(const sp::vector3f& p1, const sp::vector3f& p2, const sp::vector3f& p3)
{
   sp::vector2f p1Vec2(p1.x, p1.y);
   sp::vector2f p2Vec2(p2.x, p2.y);
   sp::vector2f p3Vec2(p3.x, p3.y);

   return Triangle(p1Vec2, p2Vec2, p3Vec2);
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::BitMap sp::Rectangle(sp::vector2f pos, sp::vector2f size)
{
    sp::BitMap bm;

    sp::vector2f corner_1 = sp::vector2f(pos.x + size.x, pos.y);
    sp::vector2f corner_2 = sp::vector2f(pos.x + size.x, pos.y - size.y);
    sp::vector2f corner_3 = sp::vector2f(pos.x, pos.y - size.y);
    
    sp::BitMap rect[4] = { sp::line(pos, corner_1),
                           sp::line(corner_1, corner_2),
                           sp::line(corner_2, corner_3),
                           sp::line(corner_3, pos) };
    
    bm.marge(rect, 4);
    return bm;
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::BitMap sp::Circle(sp::vector2f pos, SP_FLOAT radius, bool scaleX)
{
   radius = std::abs(radius); //Change radius to positive
   sp::vector2i v_pos = sp::coordConverter::normalToViewPosI(pos);
   
   //Radius scaling-------------
   int v_radius;
   if(scaleX)
      v_radius = sp::coordConverter::nromalToViewSizeI(sp::vector2f(radius, radius)).x;
   else
      v_radius = sp::coordConverter::nromalToViewSizeI(sp::vector2f(radius, radius)).y;
   //---------------------------
   
   //Create the bitMap----------
   sp::vector2i v_size = sp::vector2i(2 * v_radius, 2 * v_radius) + sp::vector2i(1, 1);
   v_pos -= sp::vector2i(v_radius, v_radius);

   sp::BitMap bm(v_pos, v_size);
   //---------------------------

   if(v_radius < 1)  //Trivial solution
      bm.m_pixelPosMap[0] = 1;

   else
   {
      //Variable initialization-
      sp::vector2i start = sp::vector2i(v_radius, v_radius); 
      sp::vector2i point = sp::vector2i(v_radius, 0);
      sp::vector2i plot = start + point;
      SP_FLOAT limit = v_radius * std::sin(M_PI / 4) + 1;
      int squaredRadiusY = v_radius * v_radius;
      //------------------------ 

      while(-point.y < limit)
      {         
         //First Quarter--------
         plot = start + point;
         PlotPointToBitmap(plot, bm);

         plot = start - vector2i(point.y, point.x);
         PlotPointToBitmap(plot, bm);
         //---------------------

         
         //Second Quarter-------
         plot = start + vector2i(point.y, -point.x);
         PlotPointToBitmap(plot, bm);

         plot = start - vector2i(point.x, -point.y);
         PlotPointToBitmap(plot, bm);
         //---------------------


         //Third Quarter--------
         plot = start - point;
         PlotPointToBitmap(plot, bm);

         plot = start + vector2i(point.y, point.x);
         PlotPointToBitmap(plot, bm);
         //---------------------

         
         //Fourth Quarter-------
         plot = start - vector2i(point.y, -point.x);
         PlotPointToBitmap(plot, bm);

         plot = start + vector2i(point.x, -point.y);
         PlotPointToBitmap(plot, bm);
         //---------------------


         //Checking where lies the next point
         SP_FLOAT inCircle = std::pow((point.x - 0.5), 2) + std::pow((point.y - 1), 2) - squaredRadiusY;
         
         if(inCircle <= 0)
            point += vector2i(0, -1); //Point in the circle
         else
            point += vector2i(-1 ,-1); //Point outside the circle
      }
   }

   return bm;
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::BitMap sp::Elipse(sp::vector2f pos, SP_FLOAT radiusX, SP_FLOAT radiusY)
{
   //Change radius to positive--
   radiusX = std::abs(radiusX);
   radiusY = std::abs(radiusY);
   //---------------------------

   //Variable initialization----
   sp::vector2i v_pos = sp::coordConverter::normalToViewPosI(pos);
   sp::vector2i v_radius = sp::coordConverter::nromalToViewSizeI(sp::vector2f(radiusX, radiusY));

   //Create the bitMap----------
   //This prevents the bitmap to be wrongly interpreted
   int max = v_radius.x;
   if(v_radius.y > max)
      max = v_radius.y;

   sp::vector2i v_size = sp::vector2i(2 * max, 2 * max) + sp::vector2i(4, 4); //Plus 4 pixels just for safety :)
   v_pos -= sp::vector2i(max, max) + sp::vector2i(2, 2);

   sp::BitMap bm(v_pos, v_size);
   //---------------------------

   //Trivial solutions----------
   if(v_radius.x < 1 && v_radius.y < 1)
      bm.m_pixelPosMap[0] = 1;
   else if (v_radius.y < 1) {
       sp::BitMap line = sp::line(sp::vector2i(v_pos.x, v_pos.y + v_size.y / 2), sp::vector2i(v_pos.x + v_size.x, v_pos.y + v_size.y / 2));
       bm.marge(line);
   }
   else if (v_radius.x < 1){
      sp::BitMap line = sp::line(sp::vector2i(v_pos.x + (v_size.x / 2), v_pos.y), sp::vector2i(v_pos.x + (v_size.x / 2), v_pos.y + v_size.y));
      bm.marge(line);
   }
   //---------------------------

   else
   {
      //Variable initialization-
      sp::vector2i start = sp::vector2i(max, max) + sp::vector2i(2, 2);
      sp::vector2i point = sp::vector2i(0, v_radius.y);
      sp::vector2i plot = start - point;

      SP_FLOAT p1 = (v_radius.y * v_radius.y) + (0.25f * v_radius.x * v_radius.x) - (v_radius.x * v_radius.x * v_radius.y);
      SP_FLOAT dx = 2 * v_radius.y * v_radius.y * point.x;
      SP_FLOAT dy = 2 * v_radius.x * v_radius.x * point.y;

      int squaredRadiusX = v_radius.x * v_radius.x;
      int squaredRadiusY = v_radius.y * v_radius.y;
      //------------------------
      
      //First region------------
      while (dx < dy)
      {
         //First quarter--------
         PlotPointToBitmap(plot, bm);
         //---------------------

         //Second quarter-------
         plot = start - vector2i(-point.x, point.y);
         PlotPointToBitmap(plot, bm);
         //---------------------

         //Thrird quarter-------
         plot = start + point;
         PlotPointToBitmap(plot, bm);
         //---------------------

         //Fourth quarter-------
         plot = start - vector2i(point.x, -point.y);
         PlotPointToBitmap(plot, bm);
         //---------------------

         if(p1 < 0)
         {
            point.x--;
            dx = dx + (2 * squaredRadiusY);
            p1 = p1 + dx + (squaredRadiusY);
         }
         else
         {
            point.x--;
            point.y--;
            dx = dx + (2 * squaredRadiusY);
            dy = dy - (2 * squaredRadiusX);
            p1 = p1 + dx - dy + (squaredRadiusY);
         }

         plot = start - point;
      }
      //------------------------

      //Variable initialization-
      SP_FLOAT p2 = ((squaredRadiusY) * ((point.x + 0.5) * (point.x + 0.5))) + 
                    ((squaredRadiusX) * ((point.y - 1) * (point.y - 1))) - 
                    (squaredRadiusX * squaredRadiusY);
      //------------------------
      
      //Second region-----------
      while(point.y >= 0)
      {
         //First quarter--------
         PlotPointToBitmap(plot, bm);
         //---------------------

         //Second quarter-------
         plot = start - vector2i(-point.x, point.y);
         PlotPointToBitmap(plot, bm);
         //---------------------

         //Third quarter--------
         plot = start + point;
         PlotPointToBitmap(plot, bm);
         //---------------------

         //Fourth quarter-------
         plot = start - vector2i(point.x, -point.y);
         PlotPointToBitmap(plot, bm);
         //---------------------

         if (p2 > 0)
         {
            point.y--;
            dy = dy - (2 * squaredRadiusX);
            p2 = p2 + (squaredRadiusX) - dy;
         }
         else
         {
            point.y--;
            point.x--;
            //point.x++; //Fun staff :)

            dx = dx + (2 * squaredRadiusY);
            dy = dy - (2 * squaredRadiusX);
            p2 = p2 + dx - dy + (squaredRadiusX);
         }

         plot = start - point;
      }
      //------------------------
   }
   return bm;
}
//-----------------------------------------------------


sp::BitMap sp::Mesh(sp::vector3f* vertex, int count, sp::Camera& cam, bool faceCulling, bool switchCullingDirection)
{
   sp::BitMap finalMesh;
   if(count % 3 != 0)
   {
      count -= count % 3;
   }

   for (int i = 0; i < count; i += 3)
   {
      bool visible = sp::faceCulling(vertex[0 + i], vertex[1 + i], vertex[2 + i]);
      if(switchCullingDirection)
         visible = !visible; 

      if(visible || !faceCulling)
      {
          /*
         std::vector<sp::vector3f> output;
         sp::clipTriangleToView(vertex[0 + i], vertex[1 + i], vertex[2 + i], output, cam);
         //std::cout << output.size() << std::endl;
         
         for (int k = 0; k < output.size(); k += 3)
         {
             sp::BitMap triangles = sp::Triangle(output[k], output[k + 1], output[k + 2]);

             if (triangles.m_pixelPosMap != nullptr)
                 finalMesh.marge(triangles);
         }
         */
         
         
         
         sp::BitMap triangles = sp::Triangle(vertex[0 + i], vertex[1 + i], vertex[2 + i]);
         if (triangles.m_pixelPosMap != nullptr)
            finalMesh.marge(triangles);            
      }
   }

   return finalMesh;
}

sp::BitMap sp::Mesh(std::vector<sp::vector3f>& vertexVec, bool faceCulling, bool switchCullingDirection)
{
   //Left Top Right Down 
   std::vector<sp::vector3f> viewPlanes = {sp::vector3f(-1.0, 0.0, 0.0), sp::vector3f(1.0, 0.0, 0.0), sp::vector3f(0.0, 1.0, 0.0), sp::vector3f(0.0, -1.0, 0.0),
                                            sp::vector3f(1.0, 0.0, 0.0),sp::vector3f(-1.0, 0.0, 0.0), sp::vector3f(0.0, -1.0, 0.0), sp::vector3f(0.0, 1.0, 0.0) };

   sp::BitMap finalMesh;
   int count = vertexVec.size(); 
   if(count % 3 != 0)
   {
      count -= count % 3;
   }

   for (int i = 0; i < count; i += 3)
   {
      bool visible = sp::faceCulling(vertexVec[0 + i], vertexVec[1 + i], vertexVec[2 + i]);
      if(switchCullingDirection)
         visible = !visible; 

      if(visible || !faceCulling)
      {         
         std::vector<sp::vector3f> output;
         sp::clipTriangleToPlanes(vertexVec[0 + i], vertexVec[1 + i], vertexVec[2 + i], output, viewPlanes);
         
         for (int k = 0; k < output.size(); k += 3)
         {
             sp::BitMap triangles = sp::Triangle(output[k], output[k + 1], output[k + 2]);
             if (triangles.m_pixelPosMap != nullptr)
                 finalMesh.marge(triangles);
         }
      }
   }

   return finalMesh;
}


//Often used function to plot points to bitmap---------
static inline void sp::PlotPointToBitmap(const sp::vector2i& plot, sp::BitMap& bm)
{
   bm.m_pixelPosMap[(plot.y * bm.m_size.x) + plot.x] = 1;
}
//-----------------------------------------------------