class Node
  attr_accessor :next_node, :value

  def initialize(value)
    @value = value
  end
end

class List
  include Enumerable
  attr_accessor :head_node, :tail_node

  def initialize(values)
    values.each do |v|
      append(Node.new(v))
    end
  end

  def to_s
    to_a.to_s
  end

  def each(&block)
    current_node = @head_node
    while current_node
      yield current_node.value.to_s
      current_node = current_node.next_node
    end
  end

  def append(new_node)
    if @head_node
      @tail_node.next_node = new_node
      @tail_node = new_node
    else
      @head_node = @tail_node = new_node
    end
  end

  def prepend(new_node)
    if @head_node
      new_node.next_node = @head_node
      @head_node = new_node
    else
      @head_node = @tail_node = new_node
    end
  end

  def is_circle?
    @head_node == @tail_node
  end

  def has_loop?
    return true if is_circle?
    pointer2 = pointer1 = @head_node

    while true do
      pointer1 = pointer1.next_node
      pointer2 = pointer2.next_node.next_node

      return true if pointer1 == pointer2
      return false unless pointer1 && pointer2
    end
  end
end


list = List.new([1])
puts list



list = List.new([1,2,3,4,5])
puts list.to_s # [1,2,3,4,5]
list.append(Node.new(6))
list.prepend(Node.new(0))
# list.append(list.head_node)
# puts list.take(20) # [0,1...,6]
# puts list.is_circle?
list.append(list.head_node.next_node.next_node)
puts list.is_circle?
puts list.has_loop?
puts list.take(20)
