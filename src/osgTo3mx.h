#pragma once

#include "Common.h"
#include "CJsonObject.hpp"

#include <osg/BoundingBox>
#include <osg/ref_ptr>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PagedLOD>
#include <osg/ProxyNode>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/MatrixTransform>
#include <osg/LineWidth>
#include <osg/Point>
#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/FileUtils>
#include <osgDB/XmlParser>
#include <osgDB/FileNameUtils>

namespace seed
{
	namespace io
	{
		struct Node
		{
			std::string id;
			osg::BoundingBox bb;
			float maxScreenDiameter;
			std::vector<std::string> children;
			std::vector<std::string> resources;
		};

		struct Resource
		{
			std::string type;
			std::string format;
			std::string id;
			
			std::string texture;
			osg::BoundingBox bb;

			std::vector<char> bufferData;
		};

		class OsgTo3mx
		{
		public:
			OsgTo3mx() {}

			~OsgTo3mx() {}

			bool Convert(const std::string&input, const std::string& output);

		private:
			bool ConvertMetadataTo3mx(const std::string& input, const std::string& outputDataRootRelative, const std::string& output);
			bool ConvertTile(const std::string& inputData, const std::string& outputData, const std::string& tileName, osg::BoundingBox& bb);
			bool ConvertOsgbTo3mxb(const std::string& input, const std::string& output, osg::BoundingBox* pbb = nullptr);

			bool GenerateMetadata(const std::string& output);
			bool Generate3mxb(const std::vector<Node>& nodes, const std::vector<Resource>& resources, const std::string& output);

			neb::CJsonObject NodeToJson(const Node& node);
			neb::CJsonObject ResourceToJson(const Resource& resource);

			void ParsePagedLOD(osg::PagedLOD* lod, int index, Node& node, Resource& resGeometry, Resource& resTexture);
			void ParseGeode(osg::Geode* geode, int index, Resource& resGeometry, Resource& resTexture);
		};
	}
}