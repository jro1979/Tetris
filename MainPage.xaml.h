//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "tetris.h"
namespace dx4_win2d
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.?
	/// </summary>
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////// MainPage //////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public ref class MainPage sealed
	{
	public:
		MainPage();
		/*void CanvasControl_Draw(Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^ sender,
			Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs^ args);*/
		//*********************************************************************************************
		//********************** GAME PLAY ***********************************************************
		//*******************************************************************************
		///////////////////////// SHAPES ////////////////////////////////
		void spawnNext(void);
		void spawnShape(void);		// Spawn a new random, active shape
		void dropShape1(int speed); // Drop current active shape 1 cell 
		void moveShapeLeft(void);   // Move current active shape 1 cell to left
		void moveShapeRight(void);  // Move current active shape 1 cell to right
		void rotateShape(void);     // Rotate current active shape to the right 1 position.
		void adjustSpeed(void);
		bool checkGameOver(void);
		void reset(void);
		//bool checkRowFilled(void);
		int checkRowFilled(void);
		//////////////////////// FLOOR  ////////////////////////////////////
		bool goodToDrop(int speed);								// Checks if current shape is ok to move down 1 pixel
		float getBaseline() { return m_baseline; }				// 
		bool getInPlay() { return m_shapeInPlay; }				// Returns true if there is an active moving shape
		void setInPlay(bool inPlay) { m_shapeInPlay = inPlay; } // Sets true/false if there is an active moving shape
		void setShape(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		///////////////////////// DRAW ////////////////////////////////////
		void drawShape(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);		// Draw current actively moving shape
		void drawNextShape(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);	// Draw next shape
		void drawGameGrid(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		//void drawSetShapes(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);	// Draw current set shapes
		void drawStatusWindow(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);// Draw status window (for testing)
		void drawTotalsWindow(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		void drawFilledRow(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		void drawGameOver(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		void drawBG(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, 
			Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender);
		void  drawGameBorder(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args); // Draw game border around playing field
	
																										//////////////////////////// CANVAS ANIMATED CONTROL ////////////////////////////////////////////
		void canvas_Draw(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender,
			Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		//void canvas_Draw_1(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		void canvas_CreateResources(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender,
			Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^ args);
		void Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void canvas_Update(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender,
			Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedUpdateEventArgs^ args);
		////////////////////////////// KEYBOARD CONTROL //////////////////////////////////////////////////
		void canvas_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
		
		//Windows::Foundation::IAsyncAction^ createResourcesAsync(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender);
		void setImage(Microsoft::Graphics::Canvas::CanvasBitmap^ image) { m_image1 = image; }
		Microsoft::Graphics::Canvas::CanvasBitmap^ getImage(void) { return m_image1; }
	private:
		bool m_gameOver;
		bool m_paused;
		bool m_displayStatus;
		int m_totalRows;	  // Number of total rows
		int m_leveledRows;    // Score: number of leveled rows
		bool m_shapeInPlay;   // True/False: active shape in play?
		bool m_readyToStart;
		// Current active shape
		int m_shapeId;        // ID: 1=Box, 2=Tee, 3=Bar, 4=El, 5=Es
		Box m_boxShape;		  // Current active Box
		TEE m_tShape;		  // Current active Tee
		Bar m_barShape;		  // Current active Bar
		Es m_esShape; 
		El m_elShape;

		// Next shapes
		int m_shapeOnDeckId;
		Box m_nextBox;
		TEE m_nextTee;
		Bar m_nextBar;
		Es m_nextEs;
		El m_nextEl;

		//Game grid of set shapes
		Shapes m_shapes;	  // SetShapes array, collection of non-moving shapes on the board
		int m_numOfShapes;    // Current number of shapes in play
		//int m_speedCounter;
		int m_fullRow;
		bool m_rowFilled;
		int m_speed;          // Drop speed for shapes in game (default=1)
		float m_baseline;	  // Lower game area border
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image1;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image2;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image3;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image4;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image5;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image6;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image7;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image8;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image9;
		Microsoft::Graphics::Canvas::CanvasBitmap^ m_image10;
		Windows::Foundation::Uri^ m_file1;
		Windows::Foundation::Uri^ m_file2;
		Windows::Foundation::Uri^ m_file3;
		Windows::Foundation::Uri^ m_file4;
		Windows::Foundation::Uri^ m_file5;
		Windows::Foundation::Uri^ m_file6;
		Windows::Foundation::Uri^ m_file7;
		Windows::Foundation::Uri^ m_file8;
		Windows::Foundation::Uri^ m_file9;
		Windows::Foundation::Uri^ m_file10 ;
		/////////////////////////////// DRAW ///////////////////////////////////////////////////
		void drawBox(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, Box box);
		void drawTee(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, TEE tee);
		void drawBar(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, Bar bar);
		void drawEs(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, Es es);
		void drawEl(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, El el);
		//void drawFloor(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
	};
	
}
