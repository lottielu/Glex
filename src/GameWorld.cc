#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = std::make_shared<GameAssetManager>(mode);

  // 3d array map
  int coords[5][5][5]=
  {		// y=  0	  		1			2		3			4
/*x=0*/	  {{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{0,0,0,0,0},{0,0,0,0,2}},
/*x=0*/	  {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{2,0,0,0,0}},
/*x=2*/	  {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{2,0,0,0,0}},
/*x=3*/	  {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{2,0,0,0,0}},
/*x=4*/	  {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{2,0,0,0,0}}
  };

  for(int x=0; x< 5;x++)
  {
	  for(int y= 0; y<5; y++)
	  {
		  for(int z=0; z<5; z++)
		  {
			  if(coords[x][y][z]==1)
			  	  {
				  // draws cube
				  	  asset_manager->AddAsset(std::make_shared<CubeAsset>(x,y,z));
			  	  }
			  if(coords[x][y][z]==2)
			  {
				  // draws pyramid
			  	  asset_manager->AddAsset(std::make_shared<Pyramid>(x,y,z));
			  }
		  }
	  }
  }
}

void GameWorld::UpdateCameraPosition(Input input_direction, int mouseX, int mouseY){

asset_manager->UpdateCameraPosition(input_direction, mouseX, mouseY);

}

void GameWorld::Draw() {
  asset_manager->Draw();

}
