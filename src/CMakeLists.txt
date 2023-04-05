
set(SOURCE_LIST 
    main.cpp 
    MainWidget.cpp
 
    FVMPolyButton.cpp
    FVMImageCore.cpp

    FVMOptionGroup.cpp
    FVMCardContainer.cpp

    FVMDaintyTown.cpp
    FVMDaintyLand.cpp
    
    FVMAnimation.cpp
    FVMFoodPolicy.cpp
    FVMGameMap.cpp
    FVMGameScene.cpp
    FVMGameObject.cpp
    FVMBulletObject.cpp
    

    FVMMetaObject.cpp
    FVMPackage.cpp


    FVMBattleCardDemo.cpp
    FVMBattleManager.cpp

    )

set (RESOURCE_LIST "E:/FVM/resource/FVMResource.qrc")

qt_add_resources(RESOURCES ${RESOURCE_LIST})
qt_add_executable(FVM ${SOURCE_LIST})   

target_link_libraries(FVM PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
)