module Rwx
	class Frame
		def on_init 
			#style "icon", "text", "icon_text"
			@toolbar = Toolbar.new(self,{style:"icon"})
			 
			@toolbar.add_tool(type:"slider", title:"スライダー", label:"slider", desc:"This is slider", cb_inst:self, cb_name:"on_slider_1" )
			 
			@image = Image.new(embed_name:"test.png")
			 
			@toolbar.add_tool(type:"button", title:"ボタン１", image:@image, label:"button1", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			@toolbar.add_tool(type:"button", title:"ボタン２", label:"button2", desc:"This is button 2", cb_inst:self, cb_name:"on_button_2" )
			 
			@toolbar.add_tool(type:"slider", title:"スライダー2", label:"slider2", desc:"This is slider2", cb_inst:self, cb_name:"on_slider_2" )
			 
			@toolbar.add_tool(type:"combo", title:"コンボ", label:"Combo", desc:"This is combo", cb_inst:self, cb_name:"on_combo",content:["コンボ1","コンボ2","コンボ3"] )
			@toolbar.add_tool(type:"drop", title:"ドロップ", label:"Drop", desc:"This is drop", cb_inst:self, cb_name:"on_drop",content:["ドロップ1","ドロップ2","ドロップ3"] )
			@toolbar.add_tool(type:"check", title:"チェック", label:"Check", desc:"This is check", cb_inst:self, cb_name:"on_check",content:["チェック1","チェック2","チェック3"] )
			@toolbar.add_tool(type:"radio", title:"ラジオ", label:"Radio", desc:"This is radio", cb_inst:self, cb_name:"on_radio",content:["ラジオ1","ラジオ2","ラジオ3"] )
			@toolbar.add_tool(type:"text_ctrl", title:"テキスト", label:"text_ctrl", desc:"This is text control", cb_inst:self )
       
		end
		 
		def on_button_1
			p "button 1"
		end
		def on_button_2
			p "button 2"
		end
		def on_slider_1(slider_value)
			#p "slider 1",slider_value
		end
		 
		def on_slider_2(slider_value)
			#p "slider 2", slider_value
		end
		 
		def on_combo(selected)
      p "combo", selected
		end
		def on_drop(selected)
      p "drop", selected
		end
		def on_check(selected)
      p "check", selected
		end
		def on_radio(selected)
      p "radio", selected
		end
	end
	 
	class App
		def on_init
			@frame = Frame.new
			@frame.set_size(1000, 500)
		end
	end
end
 
app = Rwx::App.new
 
