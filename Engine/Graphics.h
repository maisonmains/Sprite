/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Surface.h"
#include "Rect.h"
#include "Vec2.h"
#include <cassert>

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( const int& x, const int& y,Color c );
	const Color& GetPixel( int x, int y ) const;

	const RectI GetScreenRect() const;
	const Vei2 GetScreenCenter() const;

	template <typename E> 
	void DrawSprite( const Vei2& p_topLeft, const Surface& p_surf, E effect )
	{
		DrawSprite( p_topLeft, p_surf.GetRect(), p_surf, effect );
	}

	template <typename E>
	void DrawSprite( Vei2& p_topLeft, const RectI& p_srcRect, const Surface& p_surf, E effect )
	{
		assert( p_srcRect.left >= 0);
		assert( p_srcRect.right <= p_surf.GetWidth() );
		assert( p_srcRect.top >= 0 );
		assert( p_srcRect.bottom <= p_surf.GetHeight() );

		DrawSprite( p_topLeft, GetScreenRect(), p_srcRect, p_surf, effect );
	}

	template <typename E>
	/*
	* Templating the function allows arbitrary
	* data types to be accepted as a parameter.
	* Being templatized will also allow for
	* template deduction, essentially we dont need to decalre
	* the type( e.g DrawSprite<Effectd::Faded>( parameters ); )
	* when calling DrawSprite.
	*/
	void DrawSprite
	(
		Vei2& p_topLeft,
		const RectI& p_clipRegion,
		const RectI& p_srcRect,
		const Surface& p_surf, 
		E effect
	)
	{
		assert( p_srcRect.left >= 0 );
		assert( p_clipRegion.left >= 0 );
		assert( p_srcRect.right <= p_surf.GetWidth() );
		assert( ( p_clipRegion.right <= Graphics::ScreenWidth ) );
		assert( p_srcRect.top >= 0 );
		assert( p_clipRegion.top >= 0 );
		assert( p_srcRect.bottom <= p_surf.GetHeight() );
		assert( ( p_clipRegion.bottom <= Graphics::ScreenHeight ) );

		Vei2 srcRectTopLeft{ p_srcRect.left, p_srcRect.top };
		Vei2 srcRectBottomRight{ p_srcRect.right, p_srcRect.bottom };

		//clip left of sprite
		if( p_topLeft.x < p_clipRegion.left )
		{
			srcRectTopLeft.x -= p_topLeft.x - p_clipRegion.left;
			p_topLeft.x = p_clipRegion.left;
		}

		//clip top of sprite
		if( p_topLeft.y < p_clipRegion.top )
		{
			srcRectTopLeft.y -= p_topLeft.y - p_clipRegion.top;
			p_topLeft.y = p_clipRegion.top;
		}

		//clip right of sprite
		if( p_topLeft.x + ( p_srcRect.GetWidth() ) >= p_clipRegion.right )
		{
			srcRectBottomRight.x -= ( p_topLeft.x + p_srcRect.GetWidth() ) - p_clipRegion.right;
		}

		//clip botto of sprite
		if( p_topLeft.y + ( p_srcRect.GetHeight() ) >= p_clipRegion.bottom )
		{
			srcRectBottomRight.y -= ( p_topLeft.y + p_srcRect.GetHeight() ) - p_clipRegion.bottom;
		}

		for( int y{ srcRectTopLeft.y }; y < srcRectBottomRight.y; y++ )
		{
			for( int x{ srcRectTopLeft.x }; x < srcRectBottomRight.x; x++ )
			{
				const int xPos = ( p_topLeft.x + ( x - srcRectTopLeft.x ) );
				const int yPos = ( p_topLeft.y + ( y - srcRectTopLeft.y ) );

				effect
				(
					*this,
					xPos,
					yPos,
					p_surf.GetPixel( x, y )
				);
			}
		}
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain{};
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice{};
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext{};
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView{};
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture{};
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView{};
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader{};
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader{};
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer{};
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout{};
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState{};
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture{};
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 1600;
	static constexpr int ScreenHeight = 800;
};