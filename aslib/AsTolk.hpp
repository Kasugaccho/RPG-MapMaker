﻿/*#######################################################################################
	Made by Kasugaccho
	Made by As Project
	https://github.com/Kasugaccho/AsLib
	wanotaitei@gmail.com

	This code is licensed under CC0.
#######################################################################################*/
#ifndef INCLUDED_AS_PROJECT_LIBRARY_TOLK
#define INCLUDED_AS_PROJECT_LIBRARY_TOLK


namespace AsLib
{

	struct WindowEvent {
		//名前
		std::vector<std::string> list_name{};
		//画像
		std::vector<AsTexture*> list_texture{};
		//音
		std::string sound;
		//文章
		std::string str;

		WindowEvent(std::vector<std::string>& name_) :list_name(name_) {}
		WindowEvent(std::vector<std::string>& name_, std::vector<AsTexture*>& t_) :list_name(name_), list_texture(t_) {}

	};

	enum :std::size_t {
		aslib_effect_event_empty,
		aslib_effect_event_zoom,
		aslib_effect_event_over_r_slide,
	};

	//ウィンドウ専用
	struct MessageWindow {
	private:
		//ウィンドウの画像
		AsTexture* main_window{ nullptr };

		//メッセージを表示するか否か
		bool is_on{ false };
		//メッセージを終了するか否か
		bool is_exit{ false };

		Pos2 pos{};
		Pos2 end_pos{};
		PosL4 size_pos{};

		std::int32_t timer{};
		bool is_timer{ false };

		std::u32string in32_str{};
		std::size_t str32_timer{};
		bool is_str32{ false };

		bool is_end_timer{ false };
		std::int32_t end_timer{};
		bool is_end_str{ true };

		//
		bool is_end_texture{ false };

		//ウィンドウとともに流される音
		AsBGM sound;
		//何番目の音を流すか
		std::int32_t count_sound{};
		//音のファイル名
		std::string sound_name{};
		//音の拡張子
		std::string sound_extension{};
		//音を再生する(実行する)
		bool is_sound = false;

		//話している人の名前
		std::string speaker_name{};

		//出力する文字列
		std::string out_str{};

		//ウィンドウ内の最大行数
		std::int32_t number_of_lines{ 5 };

		//ウィンドウのデフォルトサイズ
		Pos4 pos_default{};
		Pos4 pos_draw_default{};
		//ふちのデフォルトサイズ
		Pos2 frame_default{};

		//ウィンドウ内のフォント
		AsFont* font;

		//早送り機能を使用するか
		bool is_fast_forward{ false };
		//早送りを実行するか
		bool is_on_fast_forward{ false };
		//一時早送りを実行するか
		bool is_on_special_fast_forward{ false };

		//文字をクリアするか
		bool on_str_clear{ true };

		//人物画像を表示するか
		AsTexture* person_texture{ nullptr };
		bool is_person{ false };
		Effect person_effect;

		AsTexture* end_anime{ nullptr };

		std::int32_t update_count{};
		std::int32_t update_end_count{};

		//名前リスト
		WindowEvent* window_event{ nullptr };

		//エフェクト
		std::size_t effect_event{ aslib_effect_event_empty };
		std::int32_t effect_count_max{};
		std::int32_t effect_count{};

	public:
#if defined(ANIME_TEXTURE_1)
		MessageWindow(AsTexture& t_) : main_window(&t_) {}
#elif defined(ANIME_TEXTURE_2)
		MessageWindow(AsTexture& t_) : main_window(&t_) {}
#endif

		MessageWindow& setWindowEvent(WindowEvent& is_) noexcept { window_event = &is_; return *this; }
		MessageWindow& setPerson(const bool is_) noexcept { is_person = is_; return *this; }
		MessageWindow& setFastForward(const bool fast_) noexcept { is_fast_forward = fast_; return *this; }
		MessageWindow& setOnFastForward(const bool fast_) noexcept { is_on_fast_forward = fast_; return *this; }
		MessageWindow& setFont(AsFont& font_) noexcept { font = &font_; return *this; }
		MessageWindow& setLine(const std::int32_t var_) noexcept {
			number_of_lines = var_ + 1;
			*font = AsFont((PosL4(pos_draw_default).h - frame_default.y * 2) / number_of_lines, font->fontName());
			return *this;
		}
		MessageWindow& setPos(const Pos4& pos_) noexcept { pos_default = pos_; pos_draw_default = pos_; return *this; }
		MessageWindow& setFrame(const Pos2& pos_) noexcept { frame_default = pos_; return *this; }
		bool isWindow() const noexcept { return is_on; }
		MessageWindow& setName(const char* const name_) noexcept {
			speaker_name = name_;
			return *this;
		}
		MessageWindow& setSound(const char* const name_, const char* const name2_ = "mp3") noexcept {
			sound_name = name_;
			sound_extension = name2_;
			is_sound = true;
			return *this;
		}

		MessageWindow& playSound() noexcept {
			if (!is_sound || sound_name[0] == 0) return *this;
			std::stringstream ss;
			std::string sound_str;
			ss << sound_name << count_sound << '.' << sound_extension;
			ss >> sound_str;
			sound.set(sound_str.c_str());
			sound.play();
			is_sound = false;
			return *this;
		}
		MessageWindow& setEffectTimer(const std::int32_t var_) noexcept { effect_count_max = var_; return *this; }
		MessageWindow& setEffect(const std::size_t var_) noexcept { effect_event = var_; return *this; }
		MessageWindow& playEffect() noexcept {
			if (effect_count_max == 0) return *this;
			if (effect_count < effect_count_max) ++effect_count;
			else return *this;

			PosA4 pos_a4(this->pos_default);
			PosL4 pos_l4(this->pos_default);

			switch (effect_event)
			{
			case aslib_effect_event_zoom:
				pos_a4.w = pos_a4.w*effect_count / effect_count_max;
				pos_a4.h = pos_a4.h*effect_count / effect_count_max;
				this->pos_draw_default = pos_a4;
				break;
			case aslib_effect_event_over_r_slide:

				//asPrint("%d+(%d-%d)*(1-%d/%d)", pos_a4.x, asWindowSize().x, pos_a4.x, effect_count, effect_count_max);
				pos_l4.x = this->pos_default.x1 + std::int32_t((asWindowSize().x - this->pos_default.x1)*(1.0f - (float(effect_count) / effect_count_max)));
				this->pos_draw_default = pos_l4;
				break;
			}
			return *this;
		}
		MessageWindow& drawWindow(const PosL4& p_, const Pos2& p2_, AsTexture& texture) noexcept {
			if (main_window == nullptr || main_window->Num() != 9) return *this;
			this->size_pos = p_;
			Pos2 p2_2(p2_);

			if (p2_.x < 0) p2_2.x = 0;
			if (p2_.y < 0) p2_2.y = 0;
			if (p2_.x > p_.w / 3) p2_2.x = p_.w / 3;
			if (p2_.y > p_.h / 3) p2_2.y = p_.h / 3;

			this->pos(this->size_pos.x + p2_2.x, this->size_pos.y + p2_2.y);
			this->end_pos(this->size_pos.x + this->size_pos.w - 2 * p2_2.x, this->size_pos.y + this->size_pos.h - 2 * p2_2.y);
			texture.draw(0, Pos4(PosL4(this->size_pos.x, this->size_pos.y, p2_2.x, p2_2.y)));
			texture.draw(1, Pos4(PosL4(this->size_pos.x + p2_2.x, this->size_pos.y, this->size_pos.w - 2 * p2_2.x, p2_2.y)));
			texture.draw(2, Pos4(PosL4(this->size_pos.x + this->size_pos.w - p2_2.x, this->size_pos.y, p2_2.x, p2_2.y)));
			texture.draw(3, Pos4(PosL4(this->size_pos.x, this->size_pos.y + p2_2.y, p2_2.x, this->size_pos.h - 2 * p2_2.y)));
			texture.draw(4, Pos4(PosL4(this->size_pos.x + p2_2.x, this->size_pos.y + p2_2.y, this->size_pos.w - 2 * p2_2.x, this->size_pos.h - 2 * p2_2.y)));
			texture.draw(5, Pos4(PosL4(this->size_pos.x + this->size_pos.w - p2_2.x, this->size_pos.y + p2_2.y, p2_2.x, this->size_pos.h - 2 * p2_2.y)));
			texture.draw(6, Pos4(PosL4(this->size_pos.x, this->size_pos.y + this->size_pos.h - p2_2.y, p2_2.x, p2_2.y)));
			texture.draw(7, Pos4(PosL4(this->size_pos.x + p2_2.x, this->size_pos.y + this->size_pos.h - p2_2.y, this->size_pos.w - 2 * p2_2.x, p2_2.y)));
			texture.draw(8, Pos4(PosL4(this->size_pos.x + this->size_pos.w - p2_2.x, this->size_pos.y + this->size_pos.h - p2_2.y, p2_2.x, p2_2.y)));
			return *this;
		}
		MessageWindow& drawWindow(const PosL4& p_, const Pos2& p2_) noexcept { return (main_window == nullptr) ? *this : drawWindow(p_, p2_, *this->main_window); }
		MessageWindow& drawWindow(const PosL4& p_) noexcept { return (main_window == nullptr) ? *this : drawWindow(p_, this->main_window->pixelSize(), *this->main_window); }
		MessageWindow& drawWindow() noexcept { return (main_window == nullptr) ? *this : drawWindow(pos_draw_default, frame_default, *this->main_window); }
		MessageWindow& drawWindow(AsTexture& texture_) noexcept { return (main_window == nullptr) ? *this : drawWindow(pos_draw_default, frame_default, texture_); }

		MessageWindow& initWindow() noexcept {
			is_on = true;
			if (sound_name[0] != 0) sound.stop();

			timer = 0;
			is_timer = false;

			str32_timer = 0;
			count_sound = 0;
			is_sound = true;

			is_end_timer = false;
			end_timer = 0;
			is_end_str = true;
			is_end_texture = false;

			effect_count=0;

			out_str = "";
			return *this;
		}
		MessageWindow& initWindow(const bool is_init_) noexcept { return (is_init_) ? this->initWindow() : *this; }
		MessageWindow& setString32(const char* const str8_) noexcept {
			if (str8_ == nullptr) return *this;
			in32_str = utf32(str8_);
			is_str32 = true;
			effect_count = 0;
			return this->initWindow();
		}
		MessageWindow& printName(AsFont& font_) noexcept {
			drawWindow(PosL4(pos_draw_default.x1, pos_draw_default.y1 - (pos_draw_default.y2 - pos_draw_default.y1) / number_of_lines - frame_default.y * 2, (pos_draw_default.x2 - pos_draw_default.x1) / 3, (pos_draw_default.y2 - pos_draw_default.y1) / number_of_lines + frame_default.y * 2), frame_default);
			font_.draw(speaker_name.c_str(), Pos2(pos.x, pos_draw_default.y1 - (pos_draw_default.y2 - pos_draw_default.y1) / number_of_lines - frame_default.y), Color(255, 255, 255));
			return *this;
		}
		MessageWindow& printName() noexcept { return printName(*this->font); }

		std::string readString(const char* const str_) noexcept {
			return asAllRead(str_);
		}
		MessageWindow& readSetString32(const char* const str_) noexcept { return setString32(this->readString(str_).c_str()); }

		MessageWindow& setString(const char* const str8_) noexcept {
			out_str = str8_;
			is_str32 = false;
			return *this;
		}
		MessageWindow& update(const std::int32_t count_) noexcept {
			++timer;
			if (timer >= count_) {
				timer = 0;
				is_timer = true;
			}
			else {
				is_timer = false;
			}
			return *this;
		}
		MessageWindow& update() noexcept { return this->update(this->update_count); return *this; }
		MessageWindow& setUpdate(const std::int32_t var_) noexcept { this->update_count = var_; return *this; }
		MessageWindow& endString() noexcept {
			is_str32 = false;
			is_end_str = true;
			is_on_fast_forward = false;
			is_on_special_fast_forward = false;
			is_exit = true;
			return *this;
		}
		MessageWindow& writeString() noexcept {
			if (!is_timer || !is_str32 || effect_count < effect_count_max) return *this;

			enum :std::size_t {
				aslib_string_number_empty,
				aslib_string_number_player_name,
			};

			static std::size_t string_number{};
			static bool is_string_number{ false };
			static std::size_t string_number_id{ aslib_string_number_empty };

			do {
				switch (in32_str[str32_timer]) {
				case U'\0':return this->endString();
				case U'\\':
					++str32_timer;
					switch (in32_str[str32_timer]) {
					case U'\0':return this->endString();
					case U'p':
						++str32_timer;
						is_string_number = true;
						string_number_id = aslib_string_number_player_name;
						break;
					case u'^':
						is_str32 = false;
						is_end_str = true;
						is_on_fast_forward = false;
						is_on_special_fast_forward = false;
						++count_sound;
						do { ++str32_timer; } while (in32_str[str32_timer] == U'\n' || in32_str[str32_timer] == U'\r');
						return 	this->next(true);;
					case U'!':
						is_str32 = false;
						is_end_str = true;
						is_on_fast_forward = false;
						is_on_special_fast_forward = false;

						on_str_clear = false;
						++str32_timer;
						break;
					case U'#':
						is_str32 = false;
						is_end_str = true;
						is_on_fast_forward = false;
						is_on_special_fast_forward = false;
						++count_sound;
						do { ++str32_timer; } while (in32_str[str32_timer] == U'\n' || in32_str[str32_timer] == U'\r');
						return *this;
					case U'>':
						++str32_timer;
						is_on_special_fast_forward = true;
						break;
					case U'<':
						++str32_timer;
						is_on_special_fast_forward = false;
						break;
					default:
						out_str += utf8(in32_str[str32_timer]);
						++str32_timer;
						break;
					}
					break;

				case U'[':
					if (is_string_number) {
						string_number = 0;

						do {
							++str32_timer;
							switch (in32_str[str32_timer])
							{//todo
							case U'0':if (string_number != 0) string_number *= 10; string_number += 0; break;
							case U'1':if (string_number != 0) string_number *= 10; string_number += 1; break;
							case U'2':if (string_number != 0) string_number *= 10; string_number += 2; break;
							case U'3':if (string_number != 0) string_number *= 10; string_number += 3; break;
							case U'4':if (string_number != 0) string_number *= 10; string_number += 4; break;
							case U'5':if (string_number != 0) string_number *= 10; string_number += 5; break;
							case U'6':if (string_number != 0) string_number *= 10; string_number += 6; break;
							case U'7':if (string_number != 0) string_number *= 10; string_number += 7; break;
							case U'8':if (string_number != 0) string_number *= 10; string_number += 8; break;
							case U'9':if (string_number != 0) string_number *= 10; string_number += 9; break;
							}
						} while (in32_str[str32_timer] != U']');
						++str32_timer;

						switch (string_number_id)
						{
						case aslib_string_number_player_name:
							if (window_event == nullptr) break;
							if (window_event->list_name.size() > string_number) this->setName(window_event->list_name[string_number].c_str());
							if (window_event->list_texture.size() > string_number) this->setPerson(*window_event->list_texture[string_number]);
							break;
						}

						is_string_number = false;
						string_number = 0;
						string_number_id = aslib_string_number_empty;

						break;
					}
				default:
					out_str += utf8(in32_str[str32_timer]);
					++str32_timer;
					break;
				}
			} while (is_on_fast_forward || is_on_special_fast_forward);
			return *this;
		}
		//終端記号をつける
		MessageWindow& updateEnd(const std::int32_t count_) noexcept {
			++end_timer;
			//タイマーがたまったら
			if (end_timer >= count_) {
				//タイマー初期化
				end_timer = 0;
				//タイマーたまったフラグ
				is_end_timer = true;
				//終端記号入れ替え
				if (is_end_str) is_end_str = false;
				else is_end_str = true;
			}
			else {
				//タイマーたまってないフラグ
				is_end_timer = false;
			}
			return *this;
		}
		MessageWindow& updateEnd() noexcept { return this->updateEnd(this->update_end_count); return *this; }
		MessageWindow& setUpdateEnd(const std::int32_t var_) noexcept { this->update_end_count = var_; return *this; }
		MessageWindow& writeEndString(const char* const end_str_) noexcept {
			if (!is_end_timer || is_str32) return *this;
			const std::size_t str_count{ std::strlen(end_str_) };
			if (is_end_str) { for (std::size_t i{}; i < str_count; ++i) out_str.pop_back(); }
			else out_str += end_str_;
			return *this;
		}
		MessageWindow& drawEndTexture(AsTexture& texture_, const Pos2& p_) noexcept {
			//表示機関に指定した画像を描画
			if (is_end_texture) texture_.draw(Pos4(end_pos.x - p_.x / 4, end_pos.y - p_.y / 4, end_pos.x, end_pos.y));

			if (!is_end_timer || is_str32) return *this;
			if (is_end_str) is_end_texture = false;
			else is_end_texture = true;
			return *this;
		}
		MessageWindow& drawEndTexture(AsTexture& texture_) noexcept {
			return drawEndTexture(texture_, Pos2(this->size_pos.h, this->size_pos.h));
		}
		MessageWindow& drawEndAnime(AsTexture& texture_, const Pos2& p_) noexcept {
			if (is_str32) return *this;
			static std::size_t draw_id{};
			//指定した画像を描画
			texture_.draw(draw_id, Pos4(end_pos.x - p_.x, end_pos.y - p_.y, end_pos.x, end_pos.y));
			if (!is_end_timer) return *this;
			if (is_end_str) {
				++draw_id;
				if (draw_id >= texture_.Num()) draw_id = 0;
			}
			return *this;
		}
		MessageWindow& drawEndAnime(AsTexture& texture_) noexcept {
			return drawEndAnime(texture_, Pos2(this->size_pos.h / 2, this->size_pos.h / 2));
		}
		MessageWindow& drawEndAnime() noexcept { return (end_anime == nullptr) ? *this : this->drawEndAnime(*end_anime); }
		MessageWindow& setEndAnime(AsTexture& texture_) noexcept { this->end_anime = &texture_; return *this; }
		MessageWindow& printString(AsFont& font_, const Color& color_ = { 255,255,255,255 }) noexcept {
			font_.draw(out_str.c_str(), this->pos, color_);
			return *this;
		}
		MessageWindow& printString(const Color& color_ = { 255,255,255,255 }) noexcept { return printString(*font, color_); }
		MessageWindow& next(const bool is_next) noexcept {
			if (!is_next) return *this;
			if (is_str32) {
				is_on_fast_forward = true;
				return *this;
			}

			if (sound_name[0] != 0) sound.stop();

			if (is_exit) {
				is_on = false;
				is_exit = false;
			}
			else is_sound = true;

			if (on_str_clear) this->out_str = "";
			on_str_clear = true;
			is_str32 = true;
			is_end_str = true;
			is_end_texture = false;
			return *this;
		}
		MessageWindow& next(const std::vector<bool>& is_next) noexcept { for (std::size_t i{}; i < is_next.size(); ++i) this->next(is_next[i]); return *this; }
		MessageWindow& next(const bool* const is_next, const std::size_t size_) noexcept { if (is_next == nullptr) return *this; for (std::size_t i{}; i < size_; ++i) this->next(is_next[i]); return *this; }
		MessageWindow& drawPerson(AsTexture& t_) noexcept {
			if (!is_person) return *this;

			t_.draw(PosA4(asWindowSize().x / 2, asWindowSize().y / 2, asWindowSize().y* t_.pixelSize().x / t_.pixelSize().y, asWindowSize().y));
			return *this;
		}
		MessageWindow& drawPerson() noexcept { return (person_texture == nullptr) ? *this : this->drawPerson(*person_texture); }
		MessageWindow& setPerson(AsTexture& t_) noexcept { this->person_texture = &t_; return *this; }
	};
}

#endif //Included AsProject Library