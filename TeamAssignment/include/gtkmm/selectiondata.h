// Generated by gmmproc 2.54.0 -- DO NOT MODIFY!
#ifndef _GTKMM_SELECTIONDATA_H
#define _GTKMM_SELECTIONDATA_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright(C) 2002 The gtkmm Development Team
 *
 * This library is free software, ) you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, ) either
 * version 2.1 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, ) without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library, ) if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <vector>

#include <gdkmm/display.h>
#include <gdkmm/pixbuf.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
extern "C" { typedef struct _GtkSelectionData GtkSelectionData; }
#endif

namespace Gtk
{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
class TextBuffer;
#endif //DOXYGEN_SHOULD_SKIP_THIS

class SelectionData
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = SelectionData;
  using BaseObjectType = GtkSelectionData;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type() G_GNUC_CONST;

  SelectionData();

  explicit SelectionData(GtkSelectionData* gobject, bool make_a_copy = true);

  SelectionData(const SelectionData& other);
  SelectionData& operator=(const SelectionData& other);

  SelectionData(SelectionData&& other) noexcept;
  SelectionData& operator=(SelectionData&& other) noexcept;

  ~SelectionData() noexcept;

  void swap(SelectionData& other) noexcept;

  ///Provides access to the underlying C instance.
  GtkSelectionData*       gobj()       { return gobject_; }

  ///Provides access to the underlying C instance.
  const GtkSelectionData* gobj() const { return gobject_; }

  ///Provides access to the underlying C instance. The caller is responsible for freeing it. Use when directly setting fields in structs.
  GtkSelectionData* gobj_copy() const;

protected:
  GtkSelectionData* gobject_;

private:

  
public:

  /** Assign a memory block of raw data.
   * Store new data into the Gtk::SelectionData object. Should _only_ be called
   * from a selection handler callback.  A 0-byte terminates the stored data.
   * The type of data is determined by get_target().
   * @param format The data format, i.e. the number of bits in a unit.
   * @param data Pointer to the data (will be copied).
   * @param length The length of the data block in bytes.
   */
  void set(int format, const guint8* data, int length);

  /** Assign a memory block of raw data.
   * Store new data into the Gtk::SelectionData object. Should _only_ be called
   * from a selection handler callback.  A 0-byte terminates the stored data.
   * @param type The type of the selection data.
   * @param format The data format, i.e. the number of bits in a unit.
   * @param data Pointer to the data (will be copied).
   * @param length The length of the data block in bytes.
   */
  void set(const std::string& type, int format, const guint8* data, int length);

  /** Assign a string of raw data.
   * Store new data into the Gtk::SelectionData object. Should _only_ be called
   * from a selection handler callback.
   * @param type The type of the selection data.
   * @param data A string that contains the data (does not have to be text).
   */
  void set(const std::string& type, const std::string& data);
  

  /** Assign UTF-8 encoded text.
   * Sets the contents of the selection from a UTF-8 encoded string.
   * The string is converted to the form determined by get_target().
   * @param data A UTF-8 encoded string.
   * @return <tt>true</tt> if the selection was successfully set,
   * otherwise <tt>false</tt>.
   */
  bool set_text(const Glib::ustring& data);
  

  /** Gets the contents of the selection data as a UTF-8 string.
   * @return If the selection data contained a recognized text type and
   * it could be converted to UTF-8, a string containing the converted text,
   * otherwise an empty string.
   */
  Glib::ustring get_text() const;
  

  /** Sets the contents of the selection from a Gdk::Pixbuf
   * The pixbuf is converted to the form determined by
   *  @a selection_data->target.
   * 
   * @newin{2,6}
   * 
   * @param pixbuf A Gdk::Pixbuf.
   * @return <tt>true</tt> if the selection was successfully set,
   * otherwise <tt>false</tt>.
   */
  bool set_pixbuf(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf);
  
  /** Gets the contents of the selection data as a Gdk::Pixbuf.
   * 
   * @newin{2,6}
   * 
   * @return If the selection data
   * contained a recognized image type and it could be converted to a
   * Gdk::Pixbuf, a newly allocated pixbuf is returned, otherwise
   * <tt>nullptr</tt>.  If the result is non-<tt>nullptr</tt> it must be freed with
   * Glib::object_unref().
   */
  Glib::RefPtr<Gdk::Pixbuf> get_pixbuf();
  
  /** Gets the contents of the selection data as a Gdk::Pixbuf.
   * 
   * @newin{2,6}
   * 
   * @return If the selection data
   * contained a recognized image type and it could be converted to a
   * Gdk::Pixbuf, a newly allocated pixbuf is returned, otherwise
   * <tt>nullptr</tt>.  If the result is non-<tt>nullptr</tt> it must be freed with
   * Glib::object_unref().
   */
  Glib::RefPtr<const Gdk::Pixbuf> get_pixbuf() const;

 
  /** Sets the contents of the selection from a list of URIs.
   * The string is converted to the form determined by
   *  @a selection_data->target.
   * 
   * @newin{2,6}
   * 
   * @param uris A <tt>nullptr</tt>-terminated array of
   * strings holding URIs.
   * @return <tt>true</tt> if the selection was successfully set,
   * otherwise <tt>false</tt>.
   */
  bool set_uris(const std::vector<Glib::ustring>& uris);
 

  /** Gets the contents of the selection data as a container of URIs.
   * 
   * @newin{2,6}
   * 
   * @return If the selection data contains a list of
   * URIs, a container containing the URIs, otherwise an empty container.
   */
  std::vector<Glib::ustring> get_uris() const;

  
  /** Retrieves the raw data of the selection.
   * 
   * @newin{2,14}
   * 
   * @return The raw data of the selection.
   */
  const guchar* get_data() const;
  
  /** Retrieves the length of the raw data of the selection.
   * 
   * @newin{2,14}
   * 
   * @return The length of the data of the selection.
   */
  int get_length() const;
  
  /** Retrieves the raw data of the selection along with its length.
   * 
   * @newin{3,0}
   * 
   * @param length Return location for length of the data segment.
   * @return The raw data of the selection.
   */
  const guchar* get_data(int& length) const;

  /** Retrieves the raw data of the selection as a std::string.
   * @return The raw data of the selection. Contains 0-bytes, if the selection data does.
   */
  std::string get_data_as_string() const;

 
  /** Retrieves the selection Gdk::Atom of the selection data.
   * 
   * @newin{2,16}
   * 
   * @return The selection Gdk::Atom of the selection data.
   */
  std::string get_selection() const;

  /** Retrieves the target of the selection.
   *
   * @newin{2,14}
   **/
  std::string get_target() const;
  

  /// See also Gtk::Clipboard::request_targets()
  std::vector<std::string> get_targets() const;
  

  /** Returns the type of the data as set by SelectionData::set().
   */
  std::string get_data_type() const; // get_type() already exists
  

  /** Retrieves the format of the selection.
   * 
   * @newin{2,14}
   * 
   * @return The format of the selection.
   */
  int get_format() const;

  
  /** Retrieves the display of the selection.
   * 
   * @newin{2,14}
   * 
   * @return The display of the selection.
   */
  Glib::RefPtr<Gdk::Display> get_display();
  
  /** Retrieves the display of the selection.
   * 
   * @newin{2,14}
   * 
   * @return The display of the selection.
   */
  Glib::RefPtr<const Gdk::Display> get_display() const;

  
  /** Given a Gtk::SelectionData object holding a list of targets,
   * determines if any of the targets in @a targets can be used to
   * provide a list or URIs.
   * 
   * @newin{2,10}
   * 
   * @return <tt>true</tt> if @a selection_data holds a list of targets,
   * and a suitable target for URI lists is included, otherwise <tt>false</tt>.
   */
  bool targets_include_uri() const;
  
  /** Given a Gtk::SelectionData object holding a list of targets,
   * determines if any of the targets in @a targets can be used to
   * provide text.
   * 
   * @return <tt>true</tt> if @a selection_data holds a list of targets,
   * and a suitable target for text is included, otherwise <tt>false</tt>.
   */
  bool targets_include_text() const;
  
  /** Given a Gtk::SelectionData object holding a list of targets,
   * determines if any of the targets in @a targets can be used to
   * provide rich text.
   * 
   * @newin{2,10}
   * 
   * @param buffer A Gtk::TextBuffer.
   * @return <tt>true</tt> if @a selection_data holds a list of targets,
   * and a suitable target for rich text is included,
   * otherwise <tt>false</tt>.
   */
  bool targets_include_rich_text(const Glib::RefPtr<TextBuffer>& buffer) const;
  
  /** Given a Gtk::SelectionData object holding a list of targets,
   * determines if any of the targets in @a targets can be used to
   * provide a Gdk::Pixbuf.
   * 
   * @newin{2,6}
   * 
   * @param writable Whether to accept only targets for which GTK+ knows
   * how to convert a pixbuf into the format.
   * @return <tt>true</tt> if @a selection_data holds a list of targets,
   * and a suitable target for images is included, otherwise <tt>false</tt>.
   */
  bool targets_include_image(bool writable =  true) const;


};

} // namespace Gtk


namespace Gtk
{

/** @relates Gtk::SelectionData
 * @param lhs The left-hand side
 * @param rhs The right-hand side
 */
inline void swap(SelectionData& lhs, SelectionData& rhs) noexcept
  { lhs.swap(rhs); }

} // namespace Gtk

namespace Glib
{

/** A Glib::wrap() method for this object.
 *
 * @param object The C instance.
 * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
 * @result A C++ instance that wraps this C instance.
 *
 * @relates Gtk::SelectionData
 */
Gtk::SelectionData wrap(GtkSelectionData* object, bool take_copy = false);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <>
class Value<Gtk::SelectionData> : public Glib::Value_Boxed<Gtk::SelectionData>
{};
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Glib


#endif /* _GTKMM_SELECTIONDATA_H */

