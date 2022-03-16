module Rwx
	class Panel
		def on_init 
			out_sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			 
			label_1 = StaticText.new(self, 'あいうえお')
			row_1_sizer.add(label_1)
			out_sizer.add(row_1_sizer)
	
			row_3_sizer = Sizer.new('box', 'horizontal')
			slider = Slider.new(self)
			 
			row_3_sizer.add(slider)
			 
			out_sizer.add_spacer(50)
			out_sizer.add(row_3_sizer)
			 
			#row_2_sizer = Sizer.new('box', 'horizontal')
			#button_1 = Button.new(self, label:'Click Here',cb_inst:self, cb_name:'on_button_click' )
			#button_2 = Button.new(self, label:'ボタン２', cb_inst:self, cb_name:'on_button_2_click' )
			#row_2_sizer.add_spacer(20)
			#row_2_sizer.add(button_1)
			#row_2_sizer.add_spacer(20)
			#row_2_sizer.add(button_2)
			# 
			#out_sizer.add_spacer(50)
			#out_sizer.add(row_2_sizer)
			 
			add_sizer(out_sizer)
			 
		end
		 
	end
	 
	class Frame
		def on_init 
			@panel = Panel.new(self)
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
