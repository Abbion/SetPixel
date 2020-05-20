#include "spgraphics.h"
#include <iostream>
#include <algorithm>

//vc_s -> view coordinates for start
//vc_e -> view coordinates for end

void sp::getDrawableAreaForLine(int* x, int* y, const vector2f& start, const vector2f& end)
{
	*x = std::abs(start.x - end.x);
	*y = std::abs(start.y - end.y);
}

sp::BitMap sp::lineLI(vector2f start, vector2f end)	//Linear interpolation line drawing. My idea :)
{
	//Optimization start drawing the line at (0, 0) and than move it

	sp::vector2f vc_s = coordConverter::normalToView(start);	//vc view coordinates
	sp::vector2f vc_e = coordConverter::normalToView(end);

	vector2i line_size(std::abs(vc_s.x - vc_e.x), std::abs(vc_s.y - vc_e.y));
	vector2i line_start_pos(std::min(vc_s.x, vc_e.x), std::min(vc_s.y, vc_e.y));

	BitMap line_segment(line_start_pos, line_size);

	float dis = distanceVec2(vc_s, vc_e);

	if ((int)dis != 0)
	{
		float delta = 1.0f / dis;
		//line_segment.pixel = new Color[(int)dis];

		float lin_int = 0;
		for (int i = 0; i < (int)dis; i++)
		{
			//line_segment.pixel_arr[i].setPosition((1.0f - linInt) * vc_s.x + linInt * vc_e.x, (1.0f - linInt) * vc_s.y + linInt * vc_e.y);
			int x_pos = ((1.0f - lin_int) * vc_s.x + lin_int * vc_e.x) - line_segment.m_startPos.x;
			int y_pos = ((1.0f - lin_int) * vc_s.y + lin_int * vc_e.y) - line_segment.m_startPos.y;
			int bit_pos = y_pos * line_segment.m_size.x + x_pos;
			line_segment.m_pixelMap[bit_pos] = 1;
			lin_int += delta;
		}
	}
	
	else
	{
		line_segment.m_pixelMap[0] = 1;
	}

	return line_segment;
}


sp::BitMap sp::line(vector2f start, vector2f end)
{
	sp::vector2f vc_s = coordConverter::normalToView(start);
	sp::vector2f vc_e = coordConverter::normalToView(end);

	vector2i line_size(std::abs(vc_s.x - vc_e.x), std::abs(vc_s.y - vc_e.y));
	vector2i line_start_pos(std::min(vc_s.x, vc_e.x), std::min(vc_s.y, vc_e.y));

	BitMap line_segment(line_start_pos, line_size);

	float x_alignment = vc_s.x - vc_e.x;
	float y_alignment = vc_s.y - vc_e.y;

	if(line_size.x == 0)	//Vertical streight line
	{		
		int y_distance = std::abs(line_segment.m_size.y);

		if(vc_s.y > vc_e.y)
			changeValues(&vc_e.y, &vc_s.y);
		
		for (int i = 0; i < y_distance; i++)
		{
			line_segment.m_pixelMap[i] = 1;
		}

		return line_segment;
	}
	

	else	//Horizontal or angled line
	{
		float slope =  y_alignment / x_alignment;

		int adjust = 1;
		//if(slope < 0)
			//adjust = -1;

		float offset = 0.0f;
		float treshold = 0.5f;

		if(slope <= 1 && slope >= -1)	//Low angle
		{
			int x_distance = std::abs(x_alignment);
			int y_start = 0;

			int delta = abs(y_alignment) * 2;
			treshold = abs(x_alignment);
			int tresholdInc = abs(x_alignment) * 2;

			bool switch_angle = false;
			if (slope < 0)
				switch_angle = true;

			for (int i = 0; i < x_distance; i++)
			{
				int bit_pos = (y_start * line_segment.m_size.x) + i;
				if (switch_angle)
				{
					//bit_pos = (abs(y_start) * line_segment.m_size.x) + (x_distance - i);
					bit_pos = (y_start * line_segment.m_size.x) + (x_distance - i);
				}
				line_segment.m_pixelMap[bit_pos] = 1;

				offset += delta;
				if(offset >= treshold)
				{
					y_start += adjust;
					treshold += tresholdInc;
				}
			}	
		}


		
		else	//High angle
		{
			int y_distance = std::abs(y_alignment);
			int x_start = 0; 

			int delta = abs(x_alignment) * 2;
			treshold = abs(y_alignment);
			int tresholdInc = abs(y_alignment) * 2;

			bool switch_angle = false;
			if (slope < 0)
				switch_angle = true;

			for(int i = 0; i < y_distance; i++)
			{
				int bit_pos = (i * line_segment.m_size.x) + x_start;
				if (switch_angle)
				{
					//bit_pos = ((y_distance -  i) * line_segment.m_size.x) + abs(x_start);
					bit_pos = ((y_distance - i) * line_segment.m_size.x) + x_start;
				}

				line_segment.m_pixelMap[bit_pos] = 1;

				offset += delta;
				if(offset >= treshold)
				{
					x_start += adjust;
					treshold += tresholdInc;
				}
			}
		}
		return line_segment;	
	}
}

/*
sp::drawable sp::triangle(float *points)
{
	drawable ret_triangle;
	ret_triangle.pixel_count = 0;

	drawable lines[3];
	int x = 0, y = 1;

	for (int i = 0; i < 3; i++)	//Drawing idividual lines
	{
		lines[i] = line(sp::vector2f(points[x], points[y]), sp::vector2f(points[(x + 2)%6], points[(y + 2)%6]));
		x += 2;
		y += 2;
		ret_triangle.pixel_count += lines[i].pixel_count; 	
	}

	ret_triangle.pixel_arr = new Pixel[ret_triangle.pixel_count];

	int pixel_counter = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < lines[i].pixel_count; j++)
		{
			ret_triangle.pixel_arr[pixel_counter] = lines[i].pixel_arr[j];
			pixel_counter++;
		}

		delete[] lines[i].pixel_arr;
	}

	return ret_triangle;
}


sp::drawable sp::fill(drawable& object, float *points, int count)
{
	int y_min, y_max, x_min, x_max;

	sp::vector2f view = coordConverter::normalToView(sp::vector2f(points[0], points[1]));

	x_min = view.x;
	x_max = view.x;
	y_min = view.y;
	y_max = view.y;

	for (int i = 2; i < count; i += 2)
	{
		sp::vector2f view = coordConverter::normalToView(sp::vector2f(points[i], points[i + 1]));
		if(view.x < x_min)
			x_min = view.x;
		else if(view.x > x_max)
			x_max = view.x;

		if(view.y < y_min)
			y_min = view.y;
		else if(view.y > y_max)
			y_max = view.y;

	}
	
	std::cout << "Max_x: " << x_max << " Min_x: " << x_min << " Max_y: " << y_max << " Min_y: " << y_min << std::endl; 

	sp::drawable filling;
	filling.pixel_count = (x_max - x_min) * (y_max - y_min);
	filling.pixel_arr = new Pixel[filling.pixel_count];

	int pixel_counter = 0;
	int coutPass = 0;
	sp::vector2i pass[2];

	for (int i = 1; i < (y_max - y_min) - 1; i++)	//Vertical line
	{
		for (int j = 1; j < (x_max - x_min) - 1; j++)	//Horizontal line
		{
			for (int k = 0; k < object.pixel_count; k++)	//Every pixel
			{
				if(object.pixel_arr[k].getPosition().y == y_min + 1)	//
				{
					pass[coutPass] = object.pixel_arr[k].getPosition();
					coutPass++;

					if(coutPass > 1)
					{
						int distance = pass[0].x - pass[1].x;
						pixel_counter += distance;
						for (int l = 0; l < distance; l++)
						{
							filling.pixel_arr[i].setPosition(x_min + l, y_min + i);
						}
						coutPass = 0;
						std::cout << distance << std::endl;
					}
				}
			}
			coutPass = 0;
		}		
	}



	return filling;
}
*/


/*
sp::BitMap sp::line(vector2f start, vector2f end)
{
	sp::vector2f vc_s = coordConverter::normalToView(start);
	sp::vector2f vc_e = coordConverter::normalToView(end);
	//drawable line_segment;

	vector2i line_size(std::abs(vc_s.x - vc_e.x), std::abs(vc_s.y - vc_e.y));
	vector2i line_start_pos(std::min(vc_s.x, vc_e.x), std::min(vc_s.y, vc_e.y));

	BitMap line_segment(line_start_pos, line_size);

	float x_alignment = vc_s.x - vc_e.x;
	float y_alignment = vc_s.y - vc_e.y;

	if(x_alignment == 0) //Vertical streight line
	{		
		int y_distance = std::abs(line_segment.m_size.y);


		if(vc_s.y > vc_e.y)
			changeValues(&vc_e.y, &vc_s.y);
		
		for (int i = 0; i < y_distance; i++)
		{
			line_segment.pixel_arr[i].setPosition(vc_s.x, vc_s.y + i);
		}
		
		line_segment.pixel_count = y_distance;

		return line_segment;
	}
	

	else	//Horizontal or angled line
	{
		float slope =  y_alignment / x_alignment;
		//float slope = line_size.y / line_size.x;

		int adjust = 1;
		if(slope < 0)
			adjust = -1;

		float offset = 0.0f;
		float treshold = 0.5f;

		if(slope <= 1 && slope >= -1)	//Low angle
		{
			int x_distance = std::abs(x_alignment) + 1;

			int delta = abs(y_alignment) * 2;
			treshold = abs(x_alignment);
			int tresholdInc = abs(x_alignment) * 2;

			int y_start = vc_s.y;
			if (vc_s.x > vc_e.x)
			{
				changeValues(&vc_s.x, &vc_e.x);
				y_start = vc_e.y;
			}

			for (int i = 0; i < x_distance; i++)
			{
				line_segment.pixel_arr[i].setPosition(vc_s.x + i, y_start);
				offset += delta;
				if(offset >= treshold)
				{
					y_start += adjust;
					treshold += tresholdInc;
				}
			}	

			line_segment.pixel_count = x_distance;
		}


		else	//High angle
		{
			int y_distance = std::abs(y_alignment) + 1;
			line_segment.pixel_arr = new Pixel[y_distance];

			int delta = abs(x_alignment) * 2;
			treshold = abs(y_alignment);
			int tresholdInc = abs(y_alignment) * 2;

			
			int x_start = vc_s.x;
			if (vc_s.y > vc_e.y)
			{
				changeValues(&vc_e.y, &vc_s.y);
				x_start = vc_e.x;
			}
			

			int x_start = 0; 

			for(int i = 0; i < y_distance; i++)
			{
				line_segment.pixel_arr[i].setPosition(x_start ,vc_s.y + i);
				offset += delta;
				if(offset >= treshold)
				{
					x_start += adjust;
					treshold += tresholdInc;
				}
			}
			line_segment.pixel_count = y_distance;
		}
		

		return line_segment;	
	}
}
*/

/*
sp::BitMap sp::line(vector2f start, vector2f end)
{
	sp::vector2f vc_s = coordConverter::normalToView(start);
	sp::vector2f vc_e = coordConverter::normalToView(end);
	//drawable line_segment;

	vector2i line_size(std::abs(vc_s.x - vc_e.x), std::abs(vc_s.y - vc_e.y));
	vector2i line_start_pos(std::min(vc_s.x, vc_e.x), std::min(vc_s.y, vc_e.y));

	BitMap line_segment(line_start_pos, line_size);

	float x_alignment = vc_s.x - vc_e.x;
	float y_alignment = vc_s.y - vc_e.y;

	if(line_size.x == 0)	//Vertical streight line
	{		
		int y_distance = std::abs(line_segment.m_size.y);

		if(vc_s.y > vc_e.y)
			changeValues(&vc_e.y, &vc_s.y);
		
		for (int i = 0; i < y_distance; i++)
		{
			line_segment.pixel_map[i] = 1;
		}

		return line_segment;
	}
	

	else	//Horizontal or angled line
	{
		float slope =  y_alignment / x_alignment;
		//float slope = line_size.y / line_size.x;

		int adjust = 1;
		if(slope < 0)
			adjust = -1;

		float offset = 0.0f;
		float treshold = 0.5f;

		if(slope <= 1 && slope >= -1)	//Low angle
		{
			int x_distance = std::abs(x_alignment) + 1;

			int delta = abs(y_alignment) * 2;
			treshold = abs(x_alignment);
			int tresholdInc = abs(x_alignment) * 2;

			bool sw = false;
			int y_start = vc_s.y;
			if (slope < 0)
			{
				changeValues(&vc_s.x, &vc_e.x);
				y_start = vc_e.y;
				sw = true;
			}


			//std::cout << "Y: " << y_start << " A: " << adjust << " X: " << line_segment.m_size.x <<  std::endl;
			
			y_start = 0;
			vc_s.x -= line_segment.m_startPos.x;

			
			//std::cout << std::endl;
			//std::cout << "a: " << adjust << " x: " << vc_s.x << std::endl;
			//std::cout << "Pos_y: " << line_segment.m_startPos.y << " x: " << line_segment.m_startPos.x << std::endl;
			//std::cout << "Size_y: " << line_segment.m_size.y << " x: " << line_segment.m_size.x << std::endl; 
			

			for (int i = 0; i < x_distance; i++)
			{
				int bit_pos = (y_start * line_segment.m_size.x) + i;
				if (sw)
				{
					bit_pos = (abs(y_start) * line_segment.m_size.x) + (x_distance - i - 1);
				}
				line_segment.pixel_map[bit_pos] = 1;

				offset += delta;
				if(offset >= treshold)
				{
					y_start += adjust;
					treshold += tresholdInc;
				}
			}	

			//line_segment.pixel_count = x_distance;
		}


		
		else	//High angle
		{
			int y_distance = std::abs(y_alignment) + 1;
			//int y_distance = std::abs(line_size.y);
			//line_segment.pixel_arr = new Pixel[y_distance];

			int delta = abs(x_alignment) * 2;
			treshold = abs(y_alignment);
			int tresholdInc = abs(y_alignment) * 2;

			
			int x_start = vc_s.x;
			bool sw = false;
			if (slope < 0)
			{
				changeValues(&vc_e.y, &vc_s.y);
				x_start = vc_e.x;
				sw = true;
			}
			

			x_start = 0; 

			for(int i = 0; i < y_distance; i++)
			{
				//line_segment.pixel_arr[i].setPosition(x_start ,vc_s.y + i);
				//int bit_pos = (i * line_segment.m_size.x) + x_start;
				int bit_pos = (i * line_segment.m_size.x) + x_start;

				if (sw)
				{
					bit_pos = ((y_distance -  i - 1) * line_segment.m_size.x) + abs(x_start);
				}

				line_segment.pixel_map[bit_pos] = 1;

				offset += delta;
				if(offset >= treshold)
				{
					x_start += adjust;
					treshold += tresholdInc;
				}
			}
			//line_segment.pixel_count = y_distance;
		}
		
		

		return line_segment;	
	}
}
*/