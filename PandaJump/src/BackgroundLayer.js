/**
 * Created by gx on 2014/7/31.
 */

var gBackgroundLayer;

var BackgroundLayer = cc.Layer.extend({
    ctor : function() {
        this._super();
        this.init();
    },
    init : function(){
        var bgColor = cc.LayerColor.create(new cc.Color(255, 255, 255, 255),
            cc.winSize.width, cc.winSize.height);
        bgColor.setAnchorPoint(new cc.Point(0.5,0.5));
        this.addChild(bgColor);
    }
});