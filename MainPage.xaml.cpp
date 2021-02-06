//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <time.h>
using namespace dx4_win2d;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Microsoft::Graphics::Canvas::Text;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Windows::UI;
using namespace concurrency;
using namespace Microsoft::Graphics::Canvas;
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
// Class:: Main Page().  Initialize MainPage properties
MainPage::MainPage()
{
	m_readyToStart = false;
	InitializeComponent();
	/*Uri^ myUri = ref new Uri("ms-appx:///Assets/stardusk.png");
	create_task(m_image->LoadAsync(canvas, myUri));*/
	m_file1 = ref new Uri(FILE1);
	m_file2 = ref new Uri(FILE2);
	m_file3 = ref new Uri(FILE3);
	m_file4 = ref new Uri(FILE4);
	m_file5 = ref new Uri(FILE5);
	m_file6 = ref new Uri(FILE6);
	m_file7 = ref new Uri(FILE7);
	m_file8 = ref new Uri(FILE8);
	m_file9 = ref new Uri(FILE9);
	m_file10 = ref new Uri(FILE10);

	reset();

}
void dx4_win2d::MainPage::reset(void)
{
	m_boxShape = Box();
	m_tShape = TEE();
	m_barShape = Bar();
	m_esShape = Es();
	m_elShape = El();
	m_shapes = Shapes();

	m_nextBox = Box();
	m_nextTee = TEE();
	m_nextBar = Bar();
	m_nextEs = Es();
	m_nextEl = El();

	m_baseline = 700;
	m_gameOver = false;
	m_shapeInPlay = false;
	//m_lowerBarrier = 0;
	m_numOfShapes = 0;
	m_fullRow = -1;
	m_rowFilled = false;
	srand((unsigned)time(NULL));
	m_speed = 2;
	m_totalRows = 0;
	m_leveledRows = 0;
	m_shapeOnDeckId = 0;
	m_paused = true;
	m_displayStatus = false;
	m_nextBox.putInNext();
	m_nextTee.putInNext();
	m_nextBar.putInNext();
	m_nextEs.putInNext();
	m_nextEl.putInNext();
	spawnNext();
}
  /// ////////////////////////////////////////////////////////////////////////////
 /// //////////////////////////// Main Game Loop /////////////////////////////
/// ///////////////////////////////////////////////////////////////////////////
void dx4_win2d::MainPage::canvas_Draw(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, 
	Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	if (m_readyToStart)
	{
		if (m_paused == false)
			drawBG(args, sender);
		if (m_displayStatus == true)
			drawStatusWindow(args);							// Draw update status window
		else
			drawTotalsWindow(args);

		drawGameBorder(args);							// Draw border around game area
		if (m_paused == false)
		{
			if (m_shapeInPlay == false)						// if no shape in play, make a new random shape object
			{
				//create_task(spawnShape()).then([this] {spawnShape(); });

				spawnNext();
				m_shapeInPlay = true;
			}
			else											// else, live shape in play.  
			{
				if (goodToDrop(0))							// Check if ok to drop 1 pixel
				{
					dropShape1(m_speed);					// Drop active shape 
					drawShape(args);						// Draw updated shape after moving
					drawNextShape(args);
				}
				else										// Live shape has bottomed out
				{
					m_shapeInPlay = false;					// Switch off shape in play to spawn new shape
					setShape(args);								// Move active shape to Set Shapes collection
					spawnShape();
				}
			}
		}
		else
		{
			if (m_gameOver == false)
			{
				drawShape(args);
				drawNextShape(args);
			}
			else
			{
				drawGameOver(args);
			}
		}

		if (m_numOfShapes > 0)							// If more than 0 Set shapes in collection, 
			drawGameGrid(args);						// draw SetShapes

	}
	
}
/// //////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// GAME PLAY ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// adjustSpeed()  adjust speed of game relative to how many pieces have spawned so far
void dx4_win2d::MainPage::adjustSpeed(void)
{
	switch (m_numOfShapes)
	{
	case 12: m_speed = 3; break;
	case 24: m_speed = 4; break;
	case 36: m_speed = 5; break;
	case 48: m_speed = 6; break;
	case 60: m_speed = 7; break;
	case 72: m_speed = 8; break;
	case 84: m_speed = 9; break;
	case 96: m_speed = 10; break;
	}
}
bool dx4_win2d::MainPage::checkGameOver(void)
{
	bool gameOver = false;
	if (m_shapes.getGridPosition(ROWS - 1, 8) != 0)
		gameOver = true;
	return gameOver;
}

// setShape().   set live shape into position.  Add shape to pile on the bottom.  Called from Main Loop
void dx4_win2d::MainPage::setShape(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args) //
{
	//m_speed = 1;
	m_numOfShapes++;
	adjustSpeed();
	switch (m_shapeId)														// Check what kind of shape is in play
	{
	case 0: // Box
		m_shapes.addToBoxes();											// increment numOfBoxes
		m_shapes.markBoxInGrid(m_boxShape);							
		break;
	case 1: // Tee
		m_shapes.addToTees();
		m_shapes.markTeeInGrid(m_tShape);
		break;
	case 2:  // Bar
		m_shapes.addToBars();
		m_shapes.markBarInGrid(m_barShape);
		break;
	case 3: // Es
		m_shapes.addToEs();
		m_shapes.markEsInGrid(m_esShape);
		break;
	case 4: // El
		m_shapes.addToEls();
		m_shapes.markElInGrid(m_elShape);
	default: break;
	}


	do // Check for any full rows
	{
		m_fullRow = checkRowFilled();
		if (m_fullRow >= 0)
		{
			drawFilledRow(args);
		}
	} while (m_fullRow >= 0);
	if (checkGameOver() == true)
	{
		m_paused = true;
		m_gameOver = true;
	}
}

// checkRowFilled() See if any rows are full, if so, remove that row and adjust floor and other setShapes
int dx4_win2d::MainPage::checkRowFilled(void)
{
	int filledRow = -1;
	for (int i = 0; i < ROWS; i++)						// Starting at row 0, check all rows in game_grid to see if any are full
	{
		if (m_shapes.checkRow(i))					    // If a row is full
		{
			m_leveledRows++;							// Add to running score
			m_shapes.shiftGameGridDown1Row(i);			// Shift cells down in game_grid
			filledRow = i;
			break;
		}
	}
	return filledRow;
}
// goodToDrop(().  Check to see if ok to lower active shape by given amount (int speed)
bool dx4_win2d::MainPage::goodToDrop(int speed)
{
	bool ok = false;
	int row = 0;
	int col = 0;
	switch (m_shapeId)
	{
	case 0: // If active box's 2 lowest cells are less than the Floor, OK.
		row = m_boxShape.getRow();
		col = m_boxShape.getCol();
		if (row > 0 && m_shapes.getGridPosition(row - 1, col) == 0 && m_shapes.getGridPosition(row - 1, col + 1) == 0)
			ok = true;
		break;
	case 1: // Check rotation of Tee.  If lowest cells are less than the Floor, OK
		row = m_tShape.getRow();
		col = m_tShape.getCol();
		switch (m_tShape.getRotation())
		{
		case 1:	if (row > 0 && m_shapes.getGridPosition(row - 1, col) == 0 && m_shapes.getGridPosition(row - 1, col - 1) == 0 &&
					m_shapes.getGridPosition(row - 1, col + 1) == 0)
					ok = true; break;
		case 2: if (row > 0 && m_shapes.getGridPosition(row - 1, col) == 0 && m_shapes.getGridPosition(row, col + 1) == 0)
					ok = true;  break;
		case 3:	if (row > 0 && m_shapes.getGridPosition(row - 1, col) == 0 && m_shapes.getGridPosition(row, col - 1) == 0 &&
					m_shapes.getGridPosition(row, col + 1) == 0)
					ok = true;  break;
		case 4:	if (row > 0 && m_shapes.getGridPosition(row - 1, col) == 0 && m_shapes.getGridPosition(row, col - 1) == 0)
					ok = true; break;
		default: break;
		} break;
	case 2: // Bar
		row = m_barShape.getRow();
		col = m_barShape.getCol();
		switch (m_barShape.getRotation())
		{
		case 1: if (row > 0 && m_shapes.getGridPosition(row - 1, col) == 0)
					ok = true; break;
		case 2: if (row > 0 && m_shapes.getGridPosition(row - 1, col - 1) == 0 && m_shapes.getGridPosition(row - 1, col) == 0 &&
					m_shapes.getGridPosition(row - 1, col + 1) == 0 && m_shapes.getGridPosition(row - 1, col + 2) == 0)
					ok = true; break;
		default: break;
		} break;
	case 3: // Es
		row = m_esShape.getRow();
		col = m_esShape.getCol();
		switch (m_esShape.getRotation())
		{
		case 1:	if (row > 1 && m_shapes.getGridPosition(row - 2, col) == 0 && m_shapes.getGridPosition(row - 1, col + 1) == 0)
					ok = true; break;
		case 2:	if (row > 0 && m_shapes.getGridPosition(row, col -1) == 0 && m_shapes.getGridPosition(row -1, col) == 0 &&
					m_shapes.getGridPosition(row -1, col + 1) == 0)
					ok = true;  break;
		case 3:	if (row > 1 && m_shapes.getGridPosition(row - 1, col) == 0 && m_shapes.getGridPosition(row -2, col + 1) == 0)
					ok = true;  break;
		case 4:	if (row > 0 && m_shapes.getGridPosition(row - 1, col -1) == 0 && m_shapes.getGridPosition(row -1, col) == 0 &&
					m_shapes.getGridPosition(row, col + 1) == 0)
					ok = true; break;
		default: break;
		} break;
	case 4: // El
		row = m_elShape.getRow();
		col = m_elShape.getCol();
		switch (m_elShape.getRotation())
		{
		case 1:	if (row > 1 && m_shapes.getGridPosition(row - 2, col) == 0 && m_shapes.getGridPosition(row - 2, col + 1) == 0)
					ok = true;  break;
		case 2:	if (row > 1 && m_shapes.getGridPosition(row - 2, col -1) == 0 && m_shapes.getGridPosition(row -1, col) == 0 &&
					m_shapes.getGridPosition(row -1, col + 1) == 0)
						ok = true;  break;
		case 3:	if (row > 1 && m_shapes.getGridPosition(row, col -1) == 0 && m_shapes.getGridPosition(row - 2, col) == 0)
					ok = true;  break;
		case 4:	if (row > 0 && m_shapes.getGridPosition(row - 1, col -1) == 0 && m_shapes.getGridPosition(row -1, col) == 0 &&
					m_shapes.getGridPosition(row -1, col + 1) == 0)
						ok = true;  break;
		default: break;
		} break;
	default: break;
	}
	return ok;
}
// dropShape1().  Lowers the active shape by amount (int speed)
void dx4_win2d::MainPage::dropShape1(int speed)
{
	switch (m_shapeId) // Check what kind of shape is active
	{
	case 0:	m_boxShape.dropBox1(speed);	break;
	case 1:	m_tShape.dropTee1(speed);	break;
	case 2:	m_barShape.dropBar1(speed);	break;
	case 3:	m_esShape.dropEs1(speed); break;
	case 4: m_elShape.dropEl1(speed); break;
	default:
		break;
	}
}
// spawnNext()
void dx4_win2d::MainPage::spawnNext(void)
{
	int random = rand() % 6;
	while (random <= 0 || random >= 6)
	{
		random = rand() & 6;
	}
	m_shapeOnDeckId = random -1;  // make next shape 0 - 4
}
// spawnShape().  Spawns a random shape.  Updates properties in MainPage.
void dx4_win2d::MainPage::spawnShape(void)
{
	//int random = rand() % 6;
	//int random = 5;
	//m_shapeOnDeckId = 1;
	switch (m_shapeOnDeckId)
	{
		case 0: // Box
			m_shapeId = 0;
			//m_shapeInPlay = true;
			m_boxShape = Box(); // make new box to set in play
			break;
		case 1: // Tee
			m_shapeId = 1;
			//m_shapeInPlay = true;
			m_tShape = TEE();
			break;
		case 2: // Bar
			m_shapeId = 2;
			//m_shapeInPlay = true;
			m_barShape = Bar();
			break;
		case 3: // Es
			m_shapeId = 3;
			//m_shapeInPlay = true;
			m_esShape = Es();
			break;
		case 4: // El
			m_shapeId = 4;
			//
			m_elShape = El();
			break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// DRAW /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// drawBG().  Draws background image on screen
void  dx4_win2d::MainPage::drawBG(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args,
	Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender)
{
	using namespace Microsoft::Graphics::Canvas;
	switch (m_speed)
	{
	case 2: if (m_image1) args->DrawingSession->DrawImage(m_image1); break;
	case 3: if (m_image2) args->DrawingSession->DrawImage(m_image2, 0, 50); break;
	case 4: if (m_image3) args->DrawingSession->DrawImage(m_image3, 25, 100); break;
	case 5: if (m_image4) args->DrawingSession->DrawImage(m_image4, 0, 50); break;
	case 6: if (m_image5) args->DrawingSession->DrawImage(m_image5, 50, 50); break;
	case 7: if (m_image6) args->DrawingSession->DrawImage(m_image6, 0, 50); break;
	case 8: if (m_image7) args->DrawingSession->DrawImage(m_image7, 0, 50); break;
	case 9: if (m_image8) args->DrawingSession->DrawImage(m_image8, 0, 100); break;
	case 10: if (m_image9) args->DrawingSession->DrawImage(m_image9, -25, 100); break;
	case 11: if (m_image10) args->DrawingSession->DrawImage(m_image10); break;
	default:
		break;
	}
}
// drawGameBorder().  Draws a thin border around game area
void  dx4_win2d::MainPage::drawGameBorder(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	GameBorder gameBorder = GameBorder();
	args->DrawingSession->DrawRectangle(gameBorder.getGameBorder(), DARKRED);
}
// drawGameOver().  Draws game over windows
void  dx4_win2d::MainPage::drawGameOver(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	GameOver gameOver = GameOver();
	String^ go = ref new String();
	go += L"\n\n   Game Over!  Press 'R' to restart ";
	Microsoft::Graphics::Canvas::Text::CanvasTextFormat^ newTextFormat;
	args->DrawingSession->DrawRectangle(gameOver.getGameOverWindow(), WHITE);
	args->DrawingSession->DrawText(go, gameOver.getGameOverWindow(), DARKRED, newTextFormat);
}
// drawFilledRow().  Draws rectangle around the full row before removing
void  dx4_win2d::MainPage::drawFilledRow(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	FilledRow fullRow = FilledRow(m_fullRow);
	args->DrawingSession->DrawRectangle(fullRow.getFilledRow(), WHITE);
	
}
void  dx4_win2d::MainPage::drawTotalsWindow(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	Totals totals = Totals();
	Microsoft::Graphics::Canvas::Text::CanvasTextFormat^ newTextFormat;
	String^ totalString = ref new String();

	totalString += L"\n  Rows leveled: ";
	totalString += m_leveledRows.ToString();
	totalString += L"\n  Total Shapes: ";
	totalString += m_numOfShapes.ToString();
	totalString += L"\n  Game speed: ";
	totalString += m_speed.ToString();

	totalString += L"\n\n  Number of Boxes: ";
	totalString += (m_shapes.getNumOfBoxes()).ToString();
	totalString += L"\n  Number Of Tees: ";
	totalString += (m_shapes.getNumOfTees()).ToString();
	totalString += L"\n  Number of Bars: ";
	totalString += (m_shapes.getNumOfBars()).ToString();
	totalString += L"\n  Number of Es: ";
	totalString += (m_shapes.getNumOfEs()).ToString();
	totalString += L"\n  Number of El: ";
	totalString += (m_shapes.getNumOfEls()).ToString();


	args->DrawingSession->DrawRectangle(totals.getTotalsWindow(), WHITE);
	args->DrawingSession->DrawText(totalString, totals.getTotalsWindow(), WHITE, newTextFormat);
}
////////////////////////////////////////////////////////////////
// drawStatusWindow().  Draws window for testing purposes only//
////////////////////////////////////////////////////////////////
void  dx4_win2d::MainPage::drawStatusWindow(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	StatusWindow statWin = StatusWindow();
	Microsoft::Graphics::Canvas::Text::CanvasTextFormat^ newTextFormat = ref new CanvasTextFormat;
	String^ shapeString = ref new String();
	//String^ fontString = ref new String();
	//fontString += L"Consolas";
	newTextFormat->FontFamily = "Consolas";
	newTextFormat->FontSize = 13;
	//// Shapes & Set Shapes
	//shapeString += L" Number of Set Shapes: ";
	//shapeString += m_numOfShapes.ToString();

	// Box position
	shapeString += L"\n  Number of Boxes: ";
	shapeString += (m_shapes.getNumOfBoxes() ).ToString();
	shapeString += L"  Row: ";
	shapeString += m_boxShape.getRow().ToString();
	shapeString += L"  Col: ";
	shapeString += m_boxShape.getCol().ToString();
	//shapeString += L"\nBox Top: ";
	//shapeString += m_boxShape.getCell(0).Y.ToString();
	//shapeString += L"\nBox LowPos: ";
	//shapeString += m_boxShape.getLowPos().ToString();
	shapeString += L"\n";

	// Tee Position
	shapeString += L"\n  Number Of Tees:  ";
	shapeString += (m_shapes.getNumOfTees() ).ToString();
	shapeString += L"  Row: ";
	shapeString += m_tShape.getRow().ToString();
	shapeString += L"  Col: ";
	shapeString += m_tShape.getCol().ToString();
	shapeString += L"\n  Rotation: ";
	shapeString += m_tShape.getRotation().ToString();
	shapeString += L"\n";

	//// Bar position
	shapeString += L"\n  Number of Bars:  ";
	shapeString += (m_shapes.getNumOfBars()).ToString();
	shapeString += L"  Row: ";
	shapeString += m_barShape.getRow().ToString();
	shapeString += L"  Col: ";
	shapeString += m_barShape.getCol().ToString();
	//shapeString += L"\nBar Top: ";
	//shapeString += m_barShape.getCell(3).Y.ToString();
	//shapeString += L"\nBar LowPos: ";
	//shapeString += m_barShape.getLowPos().ToString();
	shapeString += L"\n";

	// Es position
	shapeString += L"\n  Number of Es:    ";
	shapeString += (m_shapes.getNumOfEs()).ToString();
	shapeString += L"  Row: ";
	shapeString += m_esShape.getRow().ToString();
	shapeString += L"  Col: ";
	shapeString += m_esShape.getCol().ToString();
	shapeString += L"\n  Rotation: ";
	shapeString += m_esShape.getRotation().ToString();
	/*shapeString += L"\nEs Top: ";
	shapeString += m_esShape.getCell(3).Y.ToString();
	shapeString += L"\nEs LowPos: ";
	shapeString += m_esShape.getLowPos().ToString();
	shapeString += L"\n";*/
	shapeString += L"\n";

	// El position
	shapeString += L"\n  Number of El:    ";
	shapeString += (m_shapes.getNumOfEls()).ToString();
	shapeString += L"  Row: ";
	shapeString += m_elShape.getRow().ToString();
	shapeString += L"  Col: ";
	shapeString += m_elShape.getCol().ToString();
	shapeString += L"\n  Rotation: ";
	shapeString += m_elShape.getRotation().ToString();
	/*shapeString += L"\nEl Top: ";
	shapeString += m_elShape.getCell(3).Y.ToString();
	shapeString += L"\nEl LowPos: ";
	shapeString += m_elShape.getLowPos().ToString();*/
	shapeString += L"\n";
	//shapeString += L"Filled row: ";
	//shapeString += m_fullRow.ToString();
	shapeString += L"\nCurrent shape Id: ";
	shapeString += m_shapeId.ToString();
	shapeString += L"\nNext shape Id:    ";
	shapeString += m_shapeOnDeckId.ToString();

	// GameGrid
	Microsoft::Graphics::Canvas::Text::CanvasTextFormat^ gridFormat = ref new CanvasTextFormat;
	String^ gridString = ref new String();
	gridFormat->FontFamily = "Consolas";
	gridFormat->FontSize = 15;
	gridString += "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	for (size_t i = 0; i < 10; i++)
	{
		gridString += L"    Row: ";
		gridString += i.ToString();
		gridString += L" : ";
		for (int j = 0; j < COLS; j++)
		{
			gridString += m_shapes.getGridPosition(i, j);
		}
		gridString += "\n";
	}

	//// Speed
	//shapeString += L"\n Speed: ";
	//shapeString += m_speed.ToString();
	
	args->DrawingSession->DrawRectangle(statWin.getStatusWindow(), BLACK);
	args->DrawingSession->FillRectangle(statWin.getStatusWindow(), WHITE);
	args->DrawingSession->DrawText(shapeString, statWin.getStatusWindow(), BLACK, newTextFormat);
	args->DrawingSession->DrawText(gridString, statWin.getStatusWindow(), BLACK, gridFormat);
	
}
// drawNextShape().  Draws next active shape.
void dx4_win2d::MainPage::drawNextShape(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	Microsoft::Graphics::Canvas::Text::CanvasTextFormat^ newTextFormat;
	String^ nextString = ref new String();
	NextWindow nextWin = NextWindow();
	nextString += L"\n\n\n\n\n\n         Next shape";

	args->DrawingSession->DrawRectangle(nextWin.getNextWindow(), Colors::White);
	args->DrawingSession->DrawText(nextString, nextWin.getNextWindow(), Colors::White, newTextFormat);

	switch (m_shapeOnDeckId)
	{
	case 0:	drawBox(args, m_nextBox); break;
	case 1:	drawTee(args, m_nextTee); break;
	case 2:	drawBar(args, m_nextBar); break;
	case 3:	drawEs(args, m_nextEs);  break;
	case 4: drawEl(args, m_nextEl);  break;
	default: break;
	}
}
// drawShape().  Draws current active shape.
void dx4_win2d::MainPage::drawShape(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	switch (m_shapeId)
	{
	case 0:	drawBox(args, m_boxShape); break;
	case 1:	drawTee(args, m_tShape); break;
	case 2:	drawBar(args, m_barShape); break;
	case 3:	drawEs(args, m_esShape);  break;
	case 4: drawEl(args, m_elShape);  break;
	default: break;
	}
}
// drawGameGrid().  Draws the game grid to status windows
void dx4_win2d::MainPage::drawGameGrid(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	Windows::Foundation::Rect tempRectangle;
	// Pixels
	float startRow = FLOOR_POS - CELLSIZE; 
	float startCol = COL_START;
	tempRectangle.Height = CELLSIZE;
	tempRectangle.Width = CELLSIZE;
	for (int i = 0, row = (int)floor(startRow); i < ROWS; i++, row -= MOVECELL)
	{
		for (int j = 0, col = (int)floor(startCol); j < COLS; j++, col += MOVECELL)
		{
			tempRectangle.X = (float)col;
			tempRectangle.Y = (float)row;
			switch (m_shapes.getGridPosition(i, j))
			{
			case 0: break; // grid is empty
			case 1: // grid cell is part of a Box
				args->DrawingSession->DrawRectangle(tempRectangle, BLACK);
				args->DrawingSession->FillRectangle(tempRectangle, BLUE); break;
			case 2:  // grid cell is part of a Tee
				args->DrawingSession->DrawRectangle(tempRectangle, BLACK);
				args->DrawingSession->FillRectangle(tempRectangle, RED);  break;
			case 3:  // grid cell is part of a Bar
				args->DrawingSession->DrawRectangle(tempRectangle, BLACK);
				args->DrawingSession->FillRectangle(tempRectangle, LIGHTGREEN); break;
			case 4: // grid cell is part of an Es
				args->DrawingSession->DrawRectangle(tempRectangle, BLACK);
				args->DrawingSession->FillRectangle(tempRectangle, PURPLE);	break;
			case 5:  // grid cell is part of an El
				args->DrawingSession->DrawRectangle(tempRectangle, BLACK);
				args->DrawingSession->FillRectangle(tempRectangle, DARKGREEN); break;
			default: break;
			}
		}
	}
}
// drawBox().  Draws the current live Box shape (m_boxShape)
void dx4_win2d::MainPage::drawBox(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, Box box)
{
	for (size_t i = 0; i < BOXCELLS; i++)
	{
		args->DrawingSession->DrawRectangle(box.getCell(i), BLACK);
		args->DrawingSession->FillRectangle(box.getCell(i), BLUE);
	}
}
// drawTee().  draws current active Tee shape.
void dx4_win2d::MainPage::drawTee(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, TEE tee)
{
	for (size_t i = 0; i < BOXCELLS; i++)
	{
		args->DrawingSession->DrawRectangle(tee.getCell(i), BLACK);
		args->DrawingSession->FillRectangle(tee.getCell(i), RED);
	}
}
// drawBar().  draws current active Tee shape.
void dx4_win2d::MainPage::drawBar(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, Bar bar)
{
	for (size_t i = 0; i < BOXCELLS; i++)
	{
		args->DrawingSession->DrawRectangle(bar.getCell(i), BLACK);
		args->DrawingSession->FillRectangle(bar.getCell(i), LIGHTGREEN);
	}
}
void dx4_win2d::MainPage::drawEs(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, Es es)
{
	for (size_t i = 0; i < BOXCELLS; i++)
	{
		args->DrawingSession->DrawRectangle(es.getCell(i), BLACK);
		args->DrawingSession->FillRectangle(es.getCell(i), PURPLE);
	}
}
void dx4_win2d::MainPage::drawEl(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args, El el)
{
	for (size_t i = 0; i < BOXCELLS; i++)
	{
		args->DrawingSession->DrawRectangle(el.getCell(i), BLACK);
		args->DrawingSession->FillRectangle(el.getCell(i), DARKGREEN);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// MOVE & ROTATE SHAPE ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void dx4_win2d::MainPage::rotateShape(void)
{
	switch (m_shapeId)
	{ // case 0: box shape doesn't rotate
	case 1: m_tShape.rotateTee();	break;
	case 2: m_barShape.rotateBar();	break;
	case 3: m_esShape.rotateEs();	break;
	case 4: m_elShape.rotateEl();	break;
	default:						break;
	}
}
// moveShapeLeft().  Moves current active shape left 1 position or cell length (25 pixels).
//					 Check Floor position against shape's position to make sure it won't run
//					 into the edge
void dx4_win2d::MainPage::moveShapeLeft(void)
{
	int col = 0;
	int row = 0;
	switch (m_shapeId)
	{
	case 0:  // BOX
		row = m_boxShape.getRow();
		col = m_boxShape.getCol();
		if (col > 0 && m_shapes.getGridPosition(row, col - 1) == 0 && m_shapes.getGridPosition(row + 1, col - 1) == 0)
		{
			m_boxShape.shiftBoxLeft(); break;
		}
	case 1: // TEE
		row = m_tShape.getRow();
		col = m_tShape.getCol();
		switch (m_tShape.getRotation())
		{
		case 1: if (col > 1 && m_shapes.getGridPosition(row, col - 2) == 0 && m_shapes.getGridPosition(row + 1, col) == 0)
				{ m_tShape.shiftTeeLeft(); } break;

		case 2: if (col > 0 && m_shapes.getGridPosition(row, col - 1) == 0 && m_shapes.getGridPosition(row + 1, col - 2) == 0 &&
			m_shapes.getGridPosition(row + 2, col - 1) == 0)
				{ m_tShape.shiftTeeLeft(); } break;
			
		case 3: if (col > 1 && m_shapes.getGridPosition(row + 1, col - 2) == 0 && m_shapes.getGridPosition(row, col - 1) == 0)
				{ m_tShape.shiftTeeLeft(); } break;
			
		case 4: if (col > 1 && m_shapes.getGridPosition(row + 1, col - 2) == 0 && m_shapes.getGridPosition(row, col - 1) == 0 &&
			m_shapes.getGridPosition(row + 2, col - 1) == 0)
				{ m_tShape.shiftTeeLeft(); }  break;
		default: break;
		} break;
	case 2: // Bar
		row = m_barShape.getRow();
		col = m_barShape.getCol();
		switch (m_barShape.getRotation())
		{
		case 1: //upright
			if (col > 0 && m_shapes.getGridPosition(row - 1, col -1) == 0 && m_shapes.getGridPosition(row, col -1) == 0 &&
				m_shapes.getGridPosition(row + 1, col -1) == 0 && m_shapes.getGridPosition(row + 2, col -1) == 0)
			{
				m_barShape.shiftBarLeft();
			}
			break;
		case 2: // rotation 2, horizontal
			if (col > 1 && m_shapes.getGridPosition(row, col - 2) == 0) { m_barShape.shiftBarLeft(); }
			break;
		default: break;
		} break; 
	case 3: // Es
		row = m_esShape.getRow();
		col = m_esShape.getCol();
		switch (m_esShape.getRotation())
		{
		case 1: //upright
			if (col > 0 && m_shapes.getGridPosition(row, col - 1) == 0 && m_shapes.getGridPosition(row -1, col - 1) == 0 &&
				m_shapes.getGridPosition(row + 1, col) == 0)
			{ m_esShape.shiftEsLeft();	} break;
		case 2: // rotation 2, 
			if (col > 1 && m_shapes.getGridPosition(row +1, col - 2) == 0 && m_shapes.getGridPosition(row, col - 1) == 0)
			{ m_esShape.shiftEsLeft(); } break;
		case 3:
			if (col > 0 && m_shapes.getGridPosition(row +1, col - 1) == 0 && m_shapes.getGridPosition(row, col - 1) == 0 &&
				m_shapes.getGridPosition(row -1, col) == 0)
			{ m_esShape.shiftEsLeft();	} break;
		case 4:
			if (col > 1 && m_shapes.getGridPosition(row + 1, col - 1) == 0 && m_shapes.getGridPosition(row, col - 2) == 0)
			{ m_esShape.shiftEsLeft(); } break;
		default:
			break;
		}
		break; 
	case 4: // El
		row = m_elShape.getRow();
		col = m_elShape.getCol();
		switch (m_elShape.getRotation())
		{
		case 1: //upright
			if (col > 0 && m_shapes.getGridPosition(row, col - 1) == 0 && m_shapes.getGridPosition(row - 1, col - 1) == 0 &&
				m_shapes.getGridPosition(row + 1, col -1) == 0)
			{
				m_elShape.shiftElLeft();
			} break;
		case 2: // rotation 2, 
			if (col > 1 && m_shapes.getGridPosition(row, col - 2) == 0 && m_shapes.getGridPosition(row -1, col - 2) == 0)
			{
				m_elShape.shiftElLeft();
			} break;
		case 3:
			if (col > 1 && m_shapes.getGridPosition(row + 1, col - 2) == 0 && m_shapes.getGridPosition(row, col - 1) == 0 &&
				m_shapes.getGridPosition(row - 1, col -1) == 0)
			{
				m_elShape.shiftElLeft();
			} break;
		case 4:
			if (col > 1 && m_shapes.getGridPosition(row, col - 2) == 0 && m_shapes.getGridPosition(row +1, col) == 0)
			{
				m_elShape.shiftElLeft();
			} break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
// moveShapeRight().  Moves current active shape right 1 position or cell length (25 pixels)
//					  Check Floor position against shape's position to make sure it won't run
//					  into the edge
void dx4_win2d::MainPage::moveShapeRight(void)
{
	int row = 0;
	int col = 0; 
	switch (m_shapeId)
	{
	case 0:  // Box shape
		row = m_boxShape.getRow();
		col = m_boxShape.getCol();
		if (col < 14 && m_shapes.getGridPosition(row, col + 2) == 0 && m_shapes.getGridPosition(row + 1, col + 2) == 0)
		{ m_boxShape.shiftBoxRight(); } break;
		
	case 1:  // Tee shape
		row = m_tShape.getRow();
		col = m_tShape.getCol();
		switch (m_tShape.getRotation())
		{
		case 1: if (col < 14 && m_shapes.getGridPosition(row, col + 2) == 0 && m_shapes.getGridPosition(row + 1, col + 1) == 0)
				{ m_tShape.shiftTeeRight(); } break;
			
		case 2: if (col < 14 && m_shapes.getGridPosition(row, col + 1) == 0 && m_shapes.getGridPosition(row + 1, col + 2) == 0 &&
			m_shapes.getGridPosition(row + 2, col + 1) == 0)
				{ m_tShape.shiftTeeRight();	} break;
			
		case 3: if (col < 14 && m_shapes.getGridPosition(row + 1, col + 2) == 0 && m_shapes.getGridPosition(row, col + 1) == 0)
				{ m_tShape.shiftTeeRight();	} break;
			
		case 4: if (col < 15 && m_shapes.getGridPosition(row + 1, col + 1) == 0 && m_shapes.getGridPosition(row, col + 1) == 0 &&
					m_shapes.getGridPosition(row + 2, col + 1) == 0)
				{ m_tShape.shiftTeeRight();	}  break;
		default: break;
		} break;
	case 2:  // Bar shape
		row = m_barShape.getRow();
		col = m_barShape.getCol();
		switch (m_barShape.getRotation())
		{
		case 1: // upright
			if (col < 15 && m_shapes.getGridPosition(row - 1, col + 1) == 0 && m_shapes.getGridPosition(row, col + 1) == 0 &&
				m_shapes.getGridPosition(row + 1, col + 1) == 0 && m_shapes.getGridPosition(row + 2, col + 1) == 0)
			{ m_barShape.shiftBarRight(); }	break;

		case 2:// horizontal
			if (col < 13 && m_shapes.getGridPosition(row, col + 3) == 0) { m_barShape.shiftBarRight(); } break;

		default: break;
		} break;
	case 3: // Es
		row = m_esShape.getRow();
		col = m_esShape.getCol();
		switch (m_esShape.getRotation())
		{
		case 1: //upright
			if (col < 14 && m_shapes.getGridPosition(row, col + 1) == 0 && m_shapes.getGridPosition(row - 1, col) == 0 &&
				m_shapes.getGridPosition(row + 1, col +1) == 0)
			{ m_esShape.shiftEsRight(); } break;
		case 2: // rotation 2, 
			if (col < 14 && m_shapes.getGridPosition(row + 1, col + 1) == 0 && m_shapes.getGridPosition(row, col + 2) == 0)
			{ m_esShape.shiftEsRight();	} break;
		case 3:
			if (col < 14 && m_shapes.getGridPosition(row + 1, col) == 0 && m_shapes.getGridPosition(row, col + 1) == 0 &&
				m_shapes.getGridPosition(row - 1, col +1) == 0)
			{ m_esShape.shiftEsRight();	} break;
		case 4:
			if (col < 14 && m_shapes.getGridPosition(row + 1, col + 2) == 0 && m_shapes.getGridPosition(row, col + 1) == 0)
			{ m_esShape.shiftEsRight();	} break;
		default: break;
		} break;
	case 4: // El
		row = m_elShape.getRow();
		col = m_elShape.getCol();
		switch (m_elShape.getRotation())
		{
		case 1: //upright
			if (col < 14 && m_shapes.getGridPosition(row, col + 1) == 0 && m_shapes.getGridPosition(row - 1, col +2) == 0 &&
				m_shapes.getGridPosition(row + 1, col + 1) == 0)
			{
				m_elShape.shiftElRight();
			} break;
		case 2: // rotation 2, 
			if (col < 14 && m_shapes.getGridPosition(row, col + 2) == 0 && m_shapes.getGridPosition(row -1, col) == 0)
			{
				m_elShape.shiftElRight();
			} break;
		case 3:
			if (col < 15 && m_shapes.getGridPosition(row + 1, col +1) == 0 && m_shapes.getGridPosition(row, col + 1) == 0 &&
				m_shapes.getGridPosition(row - 1, col + 1) == 0)
			{
				m_elShape.shiftElRight();
			} break;
		case 4:
			if (col < 14 && m_shapes.getGridPosition(row + 1, col + 2) == 0 && m_shapes.getGridPosition(row, col + 2) == 0)
			{
				m_elShape.shiftElRight();
			} break;
		default: break;
		} break;
	}// end shapes
}
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// CONTROL //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// canvas_KeyDown().  Key Down Event.  Keyboard control for user.
void dx4_win2d::MainPage::canvas_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	using Windows::System::VirtualKey;
	Windows::System::VirtualKey Key;
	Key = e->Key;

	switch (Key)
	{
	case VirtualKey::Down:	while (goodToDrop(55))	{ dropShape1(5); }	break;
	case VirtualKey::Up:    rotateShape();	 break;
	case VirtualKey::Left: 	moveShapeLeft(); break;
	case VirtualKey::Right:	moveShapeRight();break;
	case VirtualKey::Add: m_speed++; break;
	case VirtualKey::Subtract: m_speed--; break;
	case VirtualKey::S:     m_readyToStart = true; m_paused = false; break;
	case VirtualKey::D:
		if (m_displayStatus == false) m_displayStatus = true;
		else if (m_displayStatus == true) m_displayStatus = false;
		break;
	case VirtualKey::P:
		if (m_paused == true && m_gameOver == false) m_paused = false;
		else if (m_paused == false) m_paused = true;
		break;
	case VirtualKey::R:	if (m_gameOver == true) { reset(); } break;
	default:
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// CANVAS CONTROL //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void dx4_win2d::MainPage::canvas_Update(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedUpdateEventArgs^ args)
{

}
void dx4_win2d::MainPage::Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->canvas->RemoveFromVisualTree();
	this->canvas = nullptr;
}
void dx4_win2d::MainPage::canvas_CreateResources(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^ args)
{
	using namespace Microsoft::Graphics::Canvas;
	//CanvasCommandList^ commandList = ref new CanvasCommandList(sender);
	//CanvasDrawingSession^ drawSession = commandList->CreateDrawingSession();
	
	Uri^ myUri = ref new Uri("ms-appx:///Assets/stardusk.png");
	Microsoft::Graphics::Canvas::CanvasBitmap^ image;
	//args->TrackAsyncAction(create_task(image->LoadAsync(sender, path)));
	
	//not using drawSession
	create_task(image->LoadAsync(sender, m_file1)).then([this](CanvasBitmap^ img1) { m_image1 = img1; });
	create_task(image->LoadAsync(sender, m_file2)).then([this](CanvasBitmap^ img2) { m_image2 = img2; });
	create_task(image->LoadAsync(sender, m_file3)).then([this](CanvasBitmap^ img3) { m_image3 = img3; });
	create_task(image->LoadAsync(sender, m_file4)).then([this](CanvasBitmap^ img4) { m_image4 = img4; });
	create_task(image->LoadAsync(sender, m_file5)).then([this](CanvasBitmap^ img5) { m_image5 = img5; });
	create_task(image->LoadAsync(sender, m_file6)).then([this](CanvasBitmap^ img6) { m_image6 = img6; });
	create_task(image->LoadAsync(sender, m_file7)).then([this](CanvasBitmap^ img7) { m_image7 = img7; });
	create_task(image->LoadAsync(sender, m_file8)).then([this](CanvasBitmap^ img8) { m_image8 = img8; });
	create_task(image->LoadAsync(sender, m_file9)).then([this](CanvasBitmap^ img9) { m_image9 = img9; });
	create_task(image->LoadAsync(sender, m_file10)).then([this](CanvasBitmap^ img10) { m_image10 = img10; });

	/*auto cr = create_async([this, image, sender, myUri](CanvasBitmap^ img)
	{
		image->LoadAsync(sender, myUri);
		m_image = img;
	});*/
	

	//args->TrackAsyncAction(createResourcesAsync(sender));

}
//Windows::Foundation::IAsyncAction^ createResourcesAsync(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender)
//{
//
//
//}
//Windows::Foundation::IAsyncAction^ dx4_win2d::MainPage::createResourcesAsync(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender)
//{
//	using namespace Microsoft::Graphics::Canvas;
//	Uri^ myUri = ref new Uri("ms-appx:///Assets/stardusk.png");
//	//String^ path = ref new String();
//	//path += L"F:\\CplusPlus\\Tetris3\\Release\\dx4_win2d\\AppX\\Assets\\stardusk.png";
//	Microsoft::Graphics::Canvas::CanvasBitmap^ image;
//	return create_async([this, &image, sender, myUri](CanvasBitmap^ img)
//	{
//		
//		image->LoadAsync(sender, myUri);
//		image = img;
//		m_image = img;
//	});
//}

