### 操控方式
按w前进, 鼠标左/右键按住拖动前进视角
### 效果节点(倒序)
1. PointLight
![img](README_img/PointLight.png)
2. SkeletalMesh
![img](README_img/SkeletalMesh2.png)
2. Bloom
![img](README_img/Bloom.png)
3. Shadow Map
![img](README_img/ShadowMap2.png)

### 工程结构
1. Actor-ActorComponent
   Entity-Component-System, 逻辑在Actor中, 数据在Component中
2. Scene
   所有Actor目前存放在Scene中
3. RHI
   dynamic render hardware interface
4. multithreading
   分为主线程(game逻辑)和Render线程
5. tripple buffering
   在FrameResourceManager中有三个buffer可以存放三组渲染数据, 因此可以接受主线程提交三组命令

# 参考目录
1. rastertek.com
   http://www.rastertek.com/
2. 龙书demo
3. dx12官方demo
4. learnopengl
   https://learnopengl-cn.readthedocs.io/zh/latest/

<!-- ### 相机操作方式
1. ↑↓←→或WASD控制相机位置
2. 按住鼠标左右键调整视角
3. QE上升与下降 -->
