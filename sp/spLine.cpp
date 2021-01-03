#include "spLine.h"
#include <algorithm>
#include <iostream>
#include "spMath.h"

//-----------------------------------------------------
sp::BitMap sp::lineLI(vector2f start, vector2f end)	//Linear interpolation line drawing. My idea :)
{
	//Optimization start drawing the line at (0, 0) and than move itH

	sp::vector2f vc_s = coordConverter::normalToViewPosF(start);	//vc view coordinates
	sp::vector2f vc_e = coordConverter::normalToViewPosF(end);
	vector2i line_size(std::abs(vc_s.x - vc_e.x), std::abs(vc_s.y - vc_e.y));
	vector2i line_start_pos(std::min(vc_s.x, vc_e.x), std::min(vc_s.y, vc_e.y));

	line_size.x++;
	line_size.y++;
	
	BitMap line_segment(line_start_pos, line_size);
	
	SP_FLOAT dis = sp::getDistance(vc_s, vc_e);

	if ((int)dis != 0)
	{
		SP_FLOAT delta = 0.95 / dis;	//Just a bit more

		for (SP_FLOAT i = 0.0; i <= 1.0; i+= delta)
		{
			int x_pos = ((1.0f - i) * vc_s.x + i * vc_e.x) - line_segment.m_startPos.x;
			int y_pos = ((1.0f - i) * vc_s.y + i * vc_e.y) - line_segment.m_startPos.y;
			int bit_pos = y_pos * line_segment.m_size.x + x_pos;
			line_segment.m_bitMapData[bit_pos] = 1;
		}
	}
	
	else
	{
		line_segment.m_bitMapData[0] = 1;
	}
	return line_segment;
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::BitMap sp::line(vector2f start, vector2f end)
{
	sp::vector2i vc_s = coordConverter::normalToViewPosI(start);
	sp::vector2i vc_e = coordConverter::normalToViewPosI(end);
	return sp::line(vc_s, vc_e);
}

sp::BitMap sp::line(vector2i start, vector2i end)
{
	sp::vector2i vc_s = start;
	sp::vector2i vc_e = end;
	
	vector2i line_size(std::abs(vc_s.x - vc_e.x), std::abs(vc_s.y - vc_e.y));
	vector2i line_start_pos(std::min(vc_s.x, vc_e.x), std::min(vc_s.y, vc_e.y));

	//Thicknes atleast one
	line_size.x++;
	line_size.y++;

	BitMap line_segment(line_start_pos, line_size);

	SP_FLOAT x_alignment = vc_s.x - vc_e.x;
	SP_FLOAT y_alignment = vc_s.y - vc_e.y;

	if(line_size.x == 0)	//Vertical streight line
	{		
		int y_distance = std::abs(line_segment.m_size.y);

		if (vc_s.y > vc_e.y)
			std::swap(vc_e.y, vc_s.y);
		
		for (int i = 0; i < y_distance; i++)
		{
			line_segment.m_bitMapData[i] = 1;
		}

		return line_segment;
	}
	
	else	//Horizontal or angled line
	{
		SP_FLOAT slope =  y_alignment / x_alignment;

		int adjust = 1;

		SP_FLOAT offset = 0.0;
		SP_FLOAT treshold = 0.5;

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

			for (int i = 0; i <= x_distance; i++)
			{
				int bit_pos = (y_start * line_segment.m_size.x) + i;
				if (switch_angle)
				{
					bit_pos = (y_start * line_segment.m_size.x) + (x_distance - i);
				}
				line_segment.m_bitMapData[bit_pos] = 1;

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

			for(int i = 0; i <= y_distance; i++)
			{
				int bit_pos = (i * line_segment.m_size.x) + x_start;
				if (switch_angle)
				{
					bit_pos = ((y_distance - i) * line_segment.m_size.x) + x_start;
				}

				line_segment.m_bitMapData[bit_pos] = 1;

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
//-----------------------------------------------------