#ifndef _SABLE_GRAPHICS_DEBUG_RENDERER_
#define _SABLE_GRAPHICS_DEBUG_RENDERER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Shader/Header.h>
#include <Sable/Graphics/Geometry/Header.h>
#include <Sable/Graphics/Debug/RendererCommand.h>
#include <Sable/Core/Geometry/Header.h>
#include <Sable/Graphics/RenderPass/RenderPass.h>
#include <Sable/Graphics/States/Header.h>
#include <Sable/Core/Math/TCBCurve.h>

namespace Sable
{

class CPlane;
class CAABoxTree;

/** 
\ingroup GraphicsDebug

Provide function to display visual debug informations.
Graphics primitives are drawed in a OpenGl way.

Those methods can be called in any ::Render method.
*/
class CDebugRenderPass : public CRenderPass
{

    DEFINE_MANAGED_CLASS( CDebugRenderPass );

public:

	/** @name DataType*/
	//@{
	//@}

    /** @name Constructor/destructor*/
    //@{
    CDebugRenderPass( CRenderer& renderer );
    ~CDebugRenderPass();
    //@}

    /** @name Accessors*/
    //@{
	CCamera* GetCamera() const;
    //@}

    /** @name Manipulator*/
    //@{
    Void PushWorldMatrix( const CMatrix4x4f& matrix );
    Void PushViewMatrix( const CMatrix4x4f& matrix );
    Void PushProjMatrix( const CMatrix4x4f& matrix );
    Void PushViewMatrix( );
    Void PushProjMatrix( );
    Void PushViewProjMatrix() ;
	Void PushDepthTestMode( Bool mode );
	Void PushFillMode( EStateFillMode mode );
    Void PushColor( const CColor& color );

    Void PopWorldMatrix( );
    Void PopViewMatrix( );
    Void PopProjMatrix( );
	Void PopViewProjMatrix();
	Void PopFillMode();
	Void PopDepthTestMode();
    Void PopColor( );

    Void DrawTexture( const CTexture2D& texture, const CVector2f& pos, const CVector2f& size );
    Void DrawSphere( const CSphere& sphere );
    Void DrawTriangle( const CTriangle& triangle );
    Void DrawTriangleList( const CArray<CTriangle>& triangles );
    Void DrawTriangle( const CVector3f& a, const CVector3f& b, const CVector3f& c );
    Void DrawSphere( const CVector3f& center, Float32 radius );
    Void DrawAABox( const CVector3f& center, const CVector3f& size );
    Void DrawAABox( const CAABox& box );
    Void DrawAABoxTree( const CAABoxTree& boxTree );
    Void DrawAABoxTreeNode( const CAABoxTree::CNode& node );
    Void DrawDisk( const CDisk& disk );
    Void DrawCylinder( const CVector3f& center, const Float32 radius, const Float32 height );
    Void DrawPlane( const CPlane& plane, const Float32 scale );
    Void DrawSpline3D( const CTCBCurve3f& spline, const UInt32 step = 20 );
    Void DrawRay( const CRay& ray, const Float32 lenght );
    Void DrawVector( const CVector3f& v, const CVector3f& o );
    Void DrawUnitGrid( const CVector3f& pos, Int32 width = 100 );
    Void DrawAdaptativeGrid( const CVector3f& pos, const CVector2f& size = CVector2f( 100.0f, 100.0f ), const CColor& col1 = CColor::Black, const CColor& col2 = CColor::Grey );
    Void DrawSpatialFrame( Float32 size );

    Void BeginLineStrip();
    Void EndLineStrip();
    Void DrawLine( const CVector3f& point );

    Void BeginLineList();
    Void EndLineList();
    Void DrawLine( const CVector3f& a, const CVector3f& b );

    Void BeginPointList();
    Void EndPointList();
    Void DrawPoint( const CVector3f& a );

    Void BeginTriangleList();
    Void EndTriangleList();

    Void Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL  );
    Bool ProcessTraversedNode( CNode& node, CRenderer& renderer );
    Void Render( CRenderer& renderer );
    //@}

private:	

    // Type
    struct SVertex
    {
        CVector3f    Pos;
        CColor      Color;
    };

    struct SVertexBuffer
    {
        SVertexBuffer();
        Void    Reset();
        Void    ResizeBuffer( UInt32 count );
        UInt32  GetVertexCapacity() const;
        SVertex*                        RawBuff;
        CRef<CGeometryVertexBuffer>     VtxBuff;
        UInt32                          CurrentVtxCount;
        UInt32                          TotalVtxCount;
    };

    // Method
    Void LoadShader();
    Void BuildMeshes();
    Void ResetStacks();
    Void DrawAABoxTreeNode( const CAABoxTree& tree, const CAABoxTree::CNode& node, UInt32 depth );

    // Attribute
    CRef<CShader>                       m_MainShader;
    CStack<CMatrix4x4f>                 m_WorldMatrixStack;
    CStack<CMatrix4x4f>                 m_ViewMatrixStack;
    CStack<CMatrix4x4f>                 m_ProjectionMatrixStack;
    CStack<CColor>                      m_ColorStack;
	CStack<Bool>						m_DepthTestStack;
	CStack<EStateFillMode>				m_FillModeStack;

    CStack<CDebugRendererCommand>       m_CommandTable;

    SVertexBuffer                       m_LineStripVB;
    SVertexBuffer                       m_LineListVB;
    SVertexBuffer                       m_PointListVB;
    SVertexBuffer                       m_TriangleListVB;

	CGeometryVertexLayout				m_VertexLayout;
    CStatesRasterizer                   m_StatesRasterizer[nStateFillMode_Count];
    CStatesDepthStencil                 m_StatesDepthStencil[2];
    CStatesBlend                        m_StatesBlend;

};

}

#endif
