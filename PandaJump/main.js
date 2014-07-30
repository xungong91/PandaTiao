cc.game.onStart = function(){
    //1.设置浏览器meta来适配屏幕，引擎内部会根据屏幕大小来设置meta的viewport值，会达到更好的屏幕适配效果。
    cc.view.adjustViewPort(true);
    //2.针对手机浏览器和PC浏览器启用不同的分辨率适配策略。
    if (cc.sys.isMobile)
    {
        cc.log("mobile");
        cc.view.setDesignResolutionSize(800, 450, cc.ResolutionPolicy.FIXED_WIDTH);
    }
    else
    {
        cc.log("web");
        cc.view.setDesignResolutionSize(800, 450, cc.ResolutionPolicy.SHOW_ALL);
    }
	cc.view.resizeWithBrowserSize(true);
    //load resources
    cc.LoaderScene.preload(g_resources, function () {
        cc.director.runScene(new GameScene());
    }, this);
};
cc.game.run();