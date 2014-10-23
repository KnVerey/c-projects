def reverse(string)
  string_array = string.split("")
  size = string_array.length
  reversed = Array.new(size=size)

  current = size - 1
  while current >= 0 do
    reversed << string_array[current]
    current -= 1
  end

  reversed.join("")
end

puts reverse("cat rat bat")
