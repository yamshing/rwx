module Rwx
	class Canvas
		def on_init()
			@mouse_x = 0
			@mouse_y = 0
			@mouse_clicked = false
			 
		end
		def on_paint()
			if @mouse_clicked
				@dc.set_brush('#aaaaaaff')
				@dc.set_pen('#ff0000',2,'dot_dash')  #dot, long_dash, short_dash, dot_dash
				@dc.draw_circle(@mouse_x, @mouse_y, 150)
			end
		end
		 
		def on_mouse_down(event)
			@mouse_x = event[:pos_x]
			@mouse_y = event[:pos_y]
			@mouse_clicked = true
			refresh
		end
		 
		def on_mouse_up(event)
			@mouse_x = event[:pos_x]
			@mouse_y = event[:pos_y]
			refresh
		end
		 
		def on_mouse_dragging(event)
			@mouse_x = event[:pos_x]
			@mouse_y = event[:pos_y]
			refresh
		end
	end
	 
	class Panel
		def on_init 
		end
	end
	 
	class LeftPanel < Panel
		def on_init 
			out_sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			label_1 = StaticText.new(self, 'あいうえお')
			row_1_sizer.add(label_1)
			out_sizer.add(row_1_sizer)
			 
			row_3_sizer = Sizer.new('box', 'horizontal')
			button_1 = Button.new(self, label:'Click Here',cb_inst:self, cb_name:'on_button_click' )
			button_2 = Button.new(self, label:'ボタン２', cb_inst:self, cb_name:'on_button_click' )
			row_3_sizer.add_spacer(20)
			row_3_sizer.add(button_1)
			row_3_sizer.add_spacer(20)
			row_3_sizer.add(button_2)
			 
			out_sizer.add_spacer(20)
			 
			out_sizer.add(row_3_sizer)
			 
			add_sizer(out_sizer)
		end
		 
		def on_button_click
			 
		end
	end
	 
	class RightPanel < Panel
		def on_init 
			out_sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			label_1 = StaticText.new(self, 'かきくけこ')
			row_1_sizer.add(label_1)
			out_sizer.add(row_1_sizer)
			add_sizer(out_sizer)
		end
	end
	 
	class Frame
		def on_init 
			 
			#@treelist = TreeList.new(self)
			#@sizer.add(@treelist)
			#set_sizer(@sizer)
			 
		end
	end
	 
	class App
		def on_init
			 
			@frame = Frame.new
			@frame.set_size(1000, 500)
			 
			#@splitter = Splitter.new(@frame)
			#@canvas = Canvas.new(@splitter)
			#@note = Notebook.new(@splitter) #,[@panel_1, @panel_2] )
			#@panel_1 = LeftPanel.new(@note)
			#@panel_2 = RightPanel.new(@note)
			#@note.add(@panel_1,'ページA')
			#@note.add(@panel_2,'ページB')
			#@splitter.split(@note, @canvas, 300, 'vertical' )
			 
			@sizer = Sizer.new('box', 'horizontal')
			@treelist = TreeList.new(@frame)
			@sizer.add(@treelist)
			@text_ctrl = TextCtrl.new(@frame, '123')
			@sizer.add(@text_ctrl)
			@frame.set_sizer(@sizer)
			 
		end
	end
end
	 
app = Rwx::App.new
