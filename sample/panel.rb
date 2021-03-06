module Rwx
	class Panel
		def on_init 
			out_sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			label_1 = StaticText.new(self, 'あいうえお')
			row_1_sizer.add(label_1)
			out_sizer.add(row_1_sizer)

			row_2_sizer = Sizer.new('box', 'horizontal')
			button_1 = Button.new(self, label:'Click Here',cb_inst:self, cb_name:'on_button_click' )
			button_2 = Button.new(self, label:'ボタン２', cb_inst:self, cb_name:'on_button_2_click' )
			row_2_sizer.add_spacer(20)
			row_2_sizer.add(button_1)
			row_2_sizer.add_spacer(20)
			row_2_sizer.add(button_2)
			 
			out_sizer.add_spacer(20)
			out_sizer.add(row_2_sizer)

			row_3_sizer = Sizer.new('box', 'horizontal')
			row_3_sizer.add_spacer(10)
			 
			@radio = RadioBox.new(self, label:'radio','content':['a','b','c'] )
			row_3_sizer.add(@radio)
			out_sizer.add_spacer(20)
			out_sizer.add(row_3_sizer)
			 
			out_sizer.add_spacer(20)
			 
			row_4_sizer = Sizer.new('box', 'horizontal')
				row_4_sizer.add_spacer(10)
				@check_1 = CheckBox.new(self, label:'チェック1')
				row_4_sizer.add(@check_1)
				 
				row_4_sizer.add_spacer(10)
				@check_2 = CheckBox.new(self, label:'チェック2')
				row_4_sizer.add(@check_2)
			out_sizer.add(row_4_sizer)
			 
			out_sizer.add_spacer(20)
			 
			row_5_sizer = Sizer.new('box', 'horizontal')
				row_5_sizer.add_spacer(10)
				label = StaticText.new(self, 'インプット')
				row_5_sizer.add(label)
				 
				@text_ctrl_1 = TextCtrl.new(self, '123')
				row_5_sizer.add(@text_ctrl_1)
				 
			out_sizer.add(row_5_sizer)
			 
			row_6_sizer = Sizer.new('box', 'horizontal')
				row_6_sizer.add_spacer(10)
				label = StaticText.new(self, 'インプット')
				row_6_sizer.add(label)
				 
				@text_ctrl_2 = TextCtrl.new(self, '555')
				row_6_sizer.add(@text_ctrl_2)
				 
			out_sizer.add(row_6_sizer)
			 
			row_7_sizer = Sizer.new('box', 'horizontal')
				row_7_sizer.add_spacer(10)
				label = StaticText.new(self, 'リスト')
				row_7_sizer.add(label)
				@list_box = ListBox.new(self);
				row_7_sizer.add(@list_box)
			out_sizer.add(row_7_sizer)
			 
			row_8_sizer = Sizer.new('box', 'horizontal')
				row_8_sizer.add_spacer(10)
				label = StaticText.new(self, 'リストコントロール')
				row_8_sizer.add(label)
				list_content = [
					['山田太郎','abc-ABC-あいうえお'],
					['木村次郎','abc-ABC-カキクケコ'],
					['木村一郎','abc-ABC-カキクケコ'],
					['山田太郎','abc-ABC-あいうえお'],
					['木村次郎','abc-ABC-カキクケコ'],
					['木村一郎','abc-ABC-カキクケコ'],
					['山田太郎','abc-ABC-あいうえお'],
					['木村次郎','abc-ABC-カキクケコ'],
					['木村一郎','abc-ABC-カキクケコ'],
				]
				 
				@list_ctrl = ListCtrl.new(self, 'header':['氏名','キー'], 'content':list_content);
				 
				row_8_sizer.add(@list_ctrl)
			out_sizer.add(row_8_sizer)
			 
			add_sizer(out_sizer)
			 
		end
		 
		def on_button_click
			result = @check_1.get_value()
			result2 = @check_2.get_value()
			 
			text_ctrl_result = @text_ctrl_1.get_value()
			 
			@text_ctrl_2.set_value(text_ctrl_result)
			 
			radio_selected = @radio.get_selection()
			 
		end
		 
		def on_button_2_click
			 
			@radio.set_selection(2)
			@check_1.set_value(true)
			 
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
